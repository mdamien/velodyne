/**
@file

@date created 2010-09-03
@author Julien Moras
*/

#include "VelodyneInterface.h"

#include "kernel/ComponentFactory.h"
#include "kernel/Log.h"
#include "PacpusTools/geodesie.h"
#include "PacpusTools/ShMem.h"

#include <boost/current_function.hpp>
#include <cmath>
#include <QFile>
#include <QTimer>
#include <vector>

namespace pacpus {

using namespace std;

DECLARE_STATIC_LOGGER("pacpus.cityvip.VelodyneInterface");

const char * VelodyneInterface::COMPONENT_NAME = "VelodyneInterface";
const char * VelodyneInterface::COMPONENT_XML_NAME = "VelodyneInterface";
const char * VelodyneInterface::SHARED_MEMORY_NAME = "VELODYNE";

const unsigned kMaxWaitForThreadTimeMs = 5000;

/// Construct the factory
static ComponentFactory<VelodyneInterface> sFactory(VelodyneInterface::COMPONENT_NAME);

VelodyneInterface::VelodyneInterface(QString name)
    : ComponentBase(name)
{
    LOG_TRACE("constructor(" << name <<")");
}

VelodyneInterface::~VelodyneInterface()
{
    LOG_TRACE("destructor");
}

ComponentBase::COMPONENT_CONFIGURATION
VelodyneInterface::configureComponent(XmlComponentConfig /* config */)
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    m_isThreadAlive = false;
    //Load Xml parameters
    //recording_ = (param.getProperty("output_file") == "true" ? true : false);
    //dbt2txt_ = (param.getProperty("output_dbt2txt") == "true" ? true : false);

    return ComponentBase::CONFIGURED_OK;
}

void VelodyneInterface::startActivity()
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    LOG_DEBUG("creating shared memory for Velodyne, size = " << sizeof(VelodynePolarData));
    // initialize shared memory
    shmem_ = new ShMem(VelodyneInterface::SHARED_MEMORY_NAME, sizeof(VelodynePolarData));

    // set thread state to alive
    VelodyneInterface::m_isThreadAlive = true;

    // start thread
    QThread::start();

    LOG_INFO("started component '" << componentName << "'");
}

void VelodyneInterface::stopActivity()
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    //Stop thread and Release variables
    VelodyneInterface::m_isThreadAlive = false;

    if (!QThread::wait(kMaxWaitForThreadTimeMs)) {
        QThread::terminate();
        LOG_ERROR("component thread '" << componentName << "' was blocking"
                  << ". It has been terminated"
                  );
    }
    delete shmem_; shmem_ = NULL;
}

void VelodyneInterface::run()
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    {
        // load lidar corrections
        string correctionsFilePath = "db.xml";
        LOG_INFO("loading Velodyne corrections file '" << correctionsFilePath.c_str() << "'");
        loadCorrections(correctionsFilePath);
    }

    //local run variables
    void * ptr; // shmem pointer for reading
    VelodynePolarData * scan;
    //    double seuil = 0.001;
    double dxy, X, Y, Z;

    while (VelodyneInterface::m_isThreadAlive) { // Variable activated by ComponentBase
        if (shmem_->wait()) {
            ptr = shmem_->read();
            memcpy(&velodyneData_, ptr, sizeof(velodyneData_));

            if (NULL != velodyneComputingStrategy) {
                velodyneComputingStrategy->processRaw(&velodyneData_);
            }
            scan = &velodyneData_;

            int pointCountTotal = 0;
            //velodyneCartData_.scanCount=scan->scanCount;
            if (VELODYNE_SCAN_SIZE < scan->range) {
                LOG_WARN("scan size (" << scan->range << ") greater than maximal allowed size (" << VELODYNE_SCAN_SIZE << ")");
            }
            velodyneCartData_.range = scan->range;
            velodyneCartData_.time=scan->time;
            velodyneCartData_.timerange=scan->timerange;

            for (int block=0; block < scan->range /*VELODYNE_SCAN_SIZE*/; ++block) {
                const double kFieldOfViewRadians = Geodesie::Deg2Rad(26.8 / 64.0);
                float alphaRadians = Geodesie::Deg2Rad((scan->polarData[block].angle) / 100.0);
                float betaRadians = 0.0;
                int k = 0;

                unsigned blockSignature = scan->polarData[block].block;
                switch (blockSignature) {
                case kVelodyneUpperBlock:
                    betaRadians = Geodesie::Deg2Rad(2) - kFieldOfViewRadians * 32;
                    k=0;
                    break;
                case kVelodyneLowerBlock:
                    betaRadians = Geodesie::Deg2Rad(2) - kFieldOfViewRadians * 64;
                    k=32;
                    break;
                default:
                    LOG_WARN("invalid signature in block " << block << ", signature = " << blockSignature);
                    continue;
                }

                //   qDebug() << "Velodyne : Cart :" << block << scan->range << alpha << beta;
                velodyneCartData_.Data[block].alpha=alphaRadians;
                velodyneCartData_.Data[block].beta=betaRadians;
                velodyneCartData_.Data[block].block=scan->polarData[block].block;

                for (int iPoint = 0; iPoint < kVelodynePointsPerBlock; ++iPoint) {
                    if (0 == scan->polarData[block].rawPoints[iPoint].distance) {
                        // point at scanner
                        continue;
                    }

                    float d = (scan->polarData[block].rawPoints[iPoint].distance) / 500.0 + m_distCor[iPoint+k] / 100.0; // increments de 2mm => /500 pour avoir des m + correction (en cm)
                    /*
                    if (d < m_seuil) {
                        break;
                    }
                    */

                    // Application des corrections du LIDAR (cf. doc velodyne)
                    double cosVertAngle = cos(betaRadians);
                    double sinVertAngle = sin(betaRadians);

                    /*  if ( -1.8< d * sinVertAngle + m_vOffsetCor[iPoint+k] / 100.0 * cosVertAngle)
                        continue;*/

                    double cosRotAngle = cos(alphaRadians - Geodesie::Deg2Rad(m_rotCor[iPoint+k]));
                    double sinRotAngle = sin(alphaRadians - Geodesie::Deg2Rad(m_rotCor[iPoint+k]));

                    double hOffsetCorr = m_hOffsetCor[iPoint+k] / 100.0;
                    double vOffsetCorr = m_vOffsetCor[iPoint+k] / 100.0;

                    dxy = d * cosVertAngle - vOffsetCorr * sinVertAngle;
                    X = dxy * sinRotAngle  - hOffsetCorr * cosRotAngle;  // x
                    Y = dxy * cosRotAngle  + hOffsetCorr * sinRotAngle;  // y
                    Z = d   * sinVertAngle + vOffsetCorr * cosVertAngle; // z

                    // on ajoute le point au vecteur qui sera transmis   la grille
                    // data.push_back(pt);
                    velodyneCartData_.Data[block].Points[iPoint].distance=d;
                    velodyneCartData_.Data[block].Points[iPoint].X=X;
                    velodyneCartData_.Data[block].Points[iPoint].Y=Y;
                    velodyneCartData_.Data[block].Points[iPoint].Z=Z;
                    velodyneCartData_.Data[block].Points[iPoint].intensity=scan->polarData[block].rawPoints[iPoint].intensity;

                    ++pointCountTotal;
                    //  qDebug() << "Velodyne : Cart :" << X << Y << Z << d << alpha << beta << scan->polarData[block].rawPoints[iPoint].intensity<< "N" << n;

                    // on met a jour beta
                    betaRadians += kFieldOfViewRadians; // 26.8 FOV vertical
                }
            }
            LOG_DEBUG("Velodyne : Cart :" << "point count total = " << pointCountTotal);
            if (NULL != velodyneComputingStrategy) {
                velodyneComputingStrategy->processCorrected(&velodyneCartData_);
            }
        } else {
            LOG_ERROR("lidar timeout");
        }
    }
    LOG_INFO("ended thread execution");
}

void VelodyneInterface::loadCorrections(const std::string & filename)
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    /////////////////////////////////////////
    // Read the DOM tree form file
    QFile f(filename.c_str());
    if (!f.open(QIODevice::ReadOnly)) {
        LOG_ERROR("cannot open file '" << filename.c_str() << "'");
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&f)) {
        LOG_ERROR("cannot read XML content of '" << filename.c_str() << "'");
        f.close();
        return;
    }
    f.close();

    /////////////////////////////////////////
    // Parse the DOM tree

    // The root node is supposed to be a "map" tag
    QDomElement root=doc.documentElement();
    root=root.firstChild().toElement();

    // Traverse its children
    QDomElement child=root.firstChild().toElement();
    while (!child.isNull()) {
        if (child.tagName() == "points_") {
            QDomElement item=child.firstChild().toElement();
            while (!item.isNull()) {
                if (item.tagName() == "item") {
                    QDomElement px=item.firstChild().toElement();
                    while (!px.isNull()) {
                        if (px.tagName() == "px") {
                            int i = 0;
                            QDomElement cor=px.firstChild().toElement();
                            while (!cor.isNull()) {
                                if (cor.tagName() == "id_") {
                                    i = cor.text().toInt();
                                }
                                if (cor.tagName() == "rotCorrection_")
                                    m_rotCor[i] = cor.text().toDouble();

                                if (cor.tagName() == "vertCorrection_") {
                                    m_vertCor[i] = cor.text().toDouble();
                                }
                                if (cor.tagName() == "distCorrection_") {
                                    m_distCor[i] = cor.text().toDouble();
                                }
                                if (cor.tagName() == "horizOffsetCorrection_") {
                                    m_hOffsetCor[i] = cor.text().toDouble();
                                }
                                if (cor.tagName() == "vertOffsetCorrection_") {
                                    m_vOffsetCor[i] = cor.text().toDouble();
                                }
                                cor = cor.nextSibling().toElement();
                            }
                        }
                        px = px.nextSibling().toElement();
                    }
                }
                item = item.nextSibling().toElement();
            }
        }
        child = child.nextSibling().toElement();
    }
}

} // namespace pacpus
