/// purpose:    Dbite Player Stereo Manager implementation
///
/// created @date 2008/01/19 - 21:23
/// @author Sergio Rodriguez
/// @version $Id: $

#include "DbtPlyStereoManager.h"

#include <iostream>

#include "kernel/ComponentManager.h"
#include "kernel/DbiteFileTypes.h"
#include "kernel/Log.h"

namespace pacpus {

using namespace std;

DECLARE_STATIC_LOGGER("pacpus.base.DbtPlyStereoManager");

/// Construction de la fabrique de composant DbtPlyStereoManager
static ComponentFactory<DbtPlyStereoManager> sFactory("DbtPlyStereoManager");

DbtPlyStereoManager::DbtPlyStereoManager(QString name)
    : DbtPlyFileManager(name)
{
    firstTime = true;
    tobeRead = NULL;

    left0      = NULL;
    right0     = NULL;
    timeStamp0 = NULL;
    timeRange0 = NULL;

    left1      = NULL;
    right1     = NULL;
    timeStamp1 = NULL;
    timeRange1 = NULL;
}

DbtPlyStereoManager::~DbtPlyStereoManager()
{
    delete tobeRead;
    delete left0;
    delete right0;
    delete timeStamp0;
    delete timeRange0;
    delete left1;
    delete right1;
    delete timeStamp1;
    delete timeRange1;
}

//processData unix
void DbtPlyStereoManager::processData(road_time_t t, road_timerange_t tr, void * buf)
{
    if (!buf) {
        return;
    }

    const size_t imageSize = width_ * height_ * depth_;

    // look at the dbt index in file manager and get the identifier of dbt structure
    hdfile_header_t::DataTypeT id = dbt_[dbtIndex_].pfile->getType();

    if (firstTime) {
        tobeRead = new ShMem("OFFSET", sizeof(bool)); //Offset pointer to read

        left0       = new ShMem("BufferLeft0", imageSize);
        right0      = new ShMem("BufferRight0", imageSize);
        timeStamp0  = new ShMem("BufferTimeStamp0", sizeof(road_time_t));
        timeRange0  = new ShMem("BufferTimeRange0", sizeof(road_timerange_t));

        left1       = new ShMem("BufferLeft1", imageSize);
        right1      = new ShMem("BufferRight1", imageSize);
        timeStamp1  = new ShMem("BufferTimeStamp1", sizeof(road_time_t));
        timeRange1  = new ShMem("BufferTimeRange1", sizeof(road_timerange_t));

        firstTime   = false;
        leftStatus  = false;
        rightStatus = false;
        offset      = false;

        if (tobeRead == NULL) {
            LOG_FATAL("Crashing because of shared memory");
        }
    }

    //dropping stereo images
    switch (id) {
    case STEREO_LEFT_IMAGE:
        if (!offset)
            left0->write(buf, imageSize);
        else
            left1->write(buf, imageSize);
        leftStatus = true;
        break;
    case STEREO_RIGHT_IMAGE:
        if (!offset)
            right0->write(buf, imageSize);
        else
            right1->write(buf, imageSize);
        rightStatus = true;
        break;
    default:
        //Unkown id data type
        break;
    }

    if ((leftStatus)&&(rightStatus)) { // synchronized stereo data is available
        //dropping time stamp
        if (!offset) {
            timeStamp0->write(&t, sizeof(road_time_t));
            timeRange0->write(&tr, sizeof(road_timerange_t));
        } else {
            timeStamp1->write(&t, sizeof(road_time_t));
            timeRange1->write(&tr, sizeof(road_timerange_t));
        }
        if (mVerbose >= 1) {
            cout << "[Shmem update Event] at " << t << std::endl;
        }
        //setting read flag
        tobeRead->write((char*)&offset, sizeof(bool));
        if (!offset)
            offset = true;
        else
            offset =false;

        leftStatus  = false;
        rightStatus = false;
    }
}

ComponentBase::COMPONENT_CONFIGURATION DbtPlyStereoManager::configureComponent(XmlComponentConfig config)
{
    //default stereo image parameters
    width_ = 320; // pixels
    height_ = 240; // pixels
    depth_ = 1; // bytes-per-pixel

    //load stereo image parameters
    width_ = param.getProperty("width").toInt();
    height_ = param.getProperty("height").toInt();
    depth_ = param.getProperty("depth").toInt();

    return DbtPlyFileManager::configureComponent(config);
}

void DbtPlyStereoManager::startActivity()
{
    DbtPlyFileManager::startActivity();
}

void DbtPlyStereoManager::stopActivity()
{
    DbtPlyFileManager::stopActivity();
}

void DbtPlyStereoManager::displayUI()
{
    // TODO: not implemented
}

void DbtPlyStereoManager::tic()
{
    tic_ = road_time();
}

void DbtPlyStereoManager::toc(char * text)
{
    cout << "duration = " << (int)(road_time() - tic_) << " " << text << "\n";
}

} // namespace pacpus
