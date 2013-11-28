#include "VelodyneConverter.h"

#include "kernel/DbiteException.h"
#include "kernel/DbiteFile.h"
#include "kernel/Log.h"
#include "PacpusTools/geodesie.h"
#include "structure/structure_velodyne.h"

#include <boost/units/cmath.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <QDomDocument>
#include <QFile>

namespace bu = boost::units;
using namespace pacpus;
using namespace std;

static const unsigned VLS_LASER_PER_FIRING = 32;
static const unsigned VLS_DIM_SCALE = 100;         // 100 cm = 1m screen scale

DECLARE_STATIC_LOGGER("pacpus.base.dbt2txt.VelodyneConverter");

class CalibrationPoint
{
public:
    typedef float Real;
    typedef boost::units::quantity<boost::units::si::plane_angle, Real> Angle;

    CalibrationPoint();
    CalibrationPoint(
        Angle rotCorrectionDegrees, Angle vertCorrectionDegrees,
        Real distCorrection, Real distCorrectionX, Real distCorrectionY,
        Real vertOffsetCorrection, Real horizOffsetCorrection,
        Real focalDistance, Real focalSlope
        );
    
    Angle getRotCorrection() const;
    Real getCosRotCorrection() const;
    Real getSinRotCorrection() const;

    Angle getVertCorrection() const;
    Real getCosVertCorrection() const;
    Real getSinVertCorrection() const;

    Real getDistCorrection() const;
    Real getDistCorrectionX() const;
    Real getDistCorrectionY() const;

    Real getVertOffsetCorrection() const;
    Real getHorizOffsetCorrection() const;

    Real getFocalDistance() const;
    Real getFocalSlope() const;

private:
    Angle mRotCorrection,
        mVertCorrection;
        
    Real mDistCorrection,
        mDistCorrectionX,
        mDistCorrectionY,
        
        mVertOffsetCorrection,
        mHorizOffsetCorrection,
        
        mFocalDistance,
        mFocalSlope;
};

CalibrationPoint::CalibrationPoint()
    : mDistCorrection(0)
    , mVertCorrection(0)
    , mRotCorrection(0)
    , mHorizOffsetCorrection(0)
    , mVertOffsetCorrection(0)
    , mDistCorrectionX(0)
    , mDistCorrectionY(0)
    , mFocalDistance(0)
    , mFocalSlope(0)
{
}

CalibrationPoint::CalibrationPoint(Angle rotCorrection, Angle vertCorrection, Real distCorrection, Real distCorrectionX, Real distCorrectionY, Real vertOffsetCorrection, Real horizOffsetCorrection, Real focalDistance, Real focalSlope)
    : mRotCorrection(rotCorrection)
    , mVertCorrection(vertCorrection)
    
    , mDistCorrection(distCorrection)
    , mDistCorrectionX(distCorrectionX)
    , mDistCorrectionY(distCorrectionY)
    
    , mVertOffsetCorrection(vertOffsetCorrection)
    , mHorizOffsetCorrection(horizOffsetCorrection)
    
    , mFocalDistance(focalDistance)
    , mFocalSlope(focalSlope)
{
}

CalibrationPoint::Real CalibrationPoint::getDistCorrection() const { return mDistCorrection; }

CalibrationPoint::Angle CalibrationPoint::getVertCorrection() const { return mVertCorrection; }
CalibrationPoint::Real CalibrationPoint::getCosVertCorrection() const { return bu::cos(mVertCorrection); }
CalibrationPoint::Real CalibrationPoint::getSinVertCorrection() const { return bu::sin(mVertCorrection); }

CalibrationPoint::Angle CalibrationPoint::getRotCorrection() const { return mRotCorrection; }
CalibrationPoint::Real CalibrationPoint::getCosRotCorrection() const { return bu::cos(mRotCorrection); }
CalibrationPoint::Real CalibrationPoint::getSinRotCorrection() const { return bu::sin(mRotCorrection); }

CalibrationPoint::Real CalibrationPoint::getHorizOffsetCorrection() const { return mHorizOffsetCorrection; }
CalibrationPoint::Real CalibrationPoint::getVertOffsetCorrection() const { return mVertOffsetCorrection; }

CalibrationPoint::Real CalibrationPoint::getDistCorrectionX() const { return mDistCorrectionX; }
CalibrationPoint::Real CalibrationPoint::getDistCorrectionY() const { return mDistCorrectionY; }

CalibrationPoint::Real CalibrationPoint::getFocalDistance() const { return mFocalDistance; }
CalibrationPoint::Real CalibrationPoint::getFocalSlope() const { return mFocalSlope; }

//////////////////////////////////////////////////////////////////////////

struct VelodyneConverter::ScanPoint
{
    /// X-Y-Z-distance
    Real x, y, z, d;

    /// intensity [0-255]
    int32_t i;
};

//////////////////////////////////////////////////////////////////////////
QString getFirstElementText(QDomElement & element, const QString tagName);

//////////////////////////////////////////////////////////////////////////

VelodyneConverter::VelodyneConverter()
{
    loadCorrections("db.xml");

    //Real alphaRadians = Geodesie::Deg2Rad(block.angle / 100.0);
    //static const Real kFieldOfViewRadians = Geodesie::Deg2Rad(26.8 / 64.0);
    //Real betaRadians = Geodesie::Deg2Rad(2) - kFieldOfViewRadians * (32 + layerOffset);

    typedef CalibrationPoint::Angle Angle;
    using namespace bu::degree;

    BOOST_ASSERT(rotCosTable.size() == rotSinTable.size());
    for (unsigned i = 0, iend = rotCosTable.size(); i < iend; ++i) {
        Angle theta = Angle(i * 0.01 * degrees);
        rotCosTable[i] = bu::cos(theta);
        rotSinTable[i] = bu::sin(theta);
    }
}

VelodyneConverter::~VelodyneConverter()
{
}

CalibrationPoint VelodyneConverter::getCalibrationPoint(unsigned laserNumber) const
{
    typedef CalibrationPoint::Angle Angle;
    using namespace bu::degree;

    return CalibrationPoint(
        Angle(mRotCorrection[laserNumber] * degrees),
        Angle(mVertCorrection[laserNumber] * degrees),
        mDistCorrection[laserNumber],
        mDistCorrectionX[laserNumber],
        mDistCorrectionY[laserNumber],
        mVertOffsetCorrection[laserNumber],
        mHorizOffsetCorrection[laserNumber],
        mFocalDistance[laserNumber],
        mFocalSlope[laserNumber]
        );
}

void VelodyneConverter::convert(const string & inputFilePath) const
{
    LOG_INFO("converting '" << inputFilePath << "'");

    // create output directory
    if (!createPath(getOutputDirectory())) {
        LOG_FATAL("cannot create output directory '" << getOutputDirectory() << "'");
        throw DbiteException("cannot create output log file");
    }
    
    // open input dbt file
    DbiteFile inputDbiteFile;
    inputDbiteFile.open(inputFilePath, ReadMode);
    if (!inputDbiteFile.isOpen()) {
        LOG_FATAL("cannot open input Dbite file '" << inputFilePath << "'");
        throw DbiteException("cannot open input Dbite file");
    }

    // declarations
    road_time_t time;
    road_timerange_t tr;
    VelodynePolarData dbtData;

    // process all scans
    const int recordCount = inputDbiteFile.getRecordCount();
    LOG_INFO("To process: " << recordCount << " Velodyne scans");
    int lastShownPercentDone = -1;
    int counter = 0;

    for (;;) {
        int percentDone = counter * 100 / recordCount;
        if (percentDone > lastShownPercentDone) {
            lastShownPercentDone = percentDone;
            LOG_INFO(percentDone << "%");
        }
        
        // get output file path
        ostringstream oss;
        oss << "scan" << counter << ".txt";
        const string outputTextFileName = oss.str();
        const string outputTextFilePath = getOutputDirectory() + getPathSeparator() + outputTextFileName;

        // read record from Dbite file
        size_t dataSize = sizeof(dbtData);
        if (!inputDbiteFile.readRecord(time, tr, reinterpret_cast<char *>(&dbtData), dataSize)) {
            break;
        }
        
        LOG_DEBUG("scan No. " << counter);
        LOG_DEBUG("#blocks  " << dbtData.range);
        // create output text file
        ofstream outputTextFile;
        outputTextFile.open(outputTextFilePath.c_str(), ios::out | ios::trunc);

        // header
        outputTextFile << "# timestamp timerange numberOfBlocks\n";
        // write data to text file
        outputTextFile
            << dbtData.time << " "
            << dbtData.timerange << " "
            << dbtData.range << "\n"
            ;
        int pointCountTotal = 0;

        // header
        outputTextFile << "# layerNumber[0-63] X[m] Y[m] Z[m] distance[m] intensity[0-255]\n";

        for (int blockIdx = 0; blockIdx < dbtData.range; ++blockIdx) {
            LOG_TRACE("block No. " << blockIdx);
            const VelodyneBlock & block = dbtData.polarData[blockIdx];
            
            unsigned blockSignature = block.block;
            int layerOffset = 0;
            switch (blockSignature) {
            case kVelodyneUpperBlock:
                layerOffset = 0;
                break;
            case kVelodyneLowerBlock:
                layerOffset = 32;
                break;
            default:
                LOG_WARN("invalid signature in block " << blockIdx << ", signature = " << blockSignature);
                continue;
            }
            //Real alphaRadians = Geodesie::Deg2Rad(block.angle / 100.0);
            //static const Real kFieldOfViewRadians = Geodesie::Deg2Rad(26.8 / 64.0);
            //Real betaRadians = Geodesie::Deg2Rad(2) - kFieldOfViewRadians * (32 + layerOffset);

            for (int iPoint = 0; iPoint < kVelodynePointsPerBlock; ++iPoint) {
                const VelodyneRawPoint & point = block.rawPoints[iPoint];
                int layerNumber = iPoint + layerOffset;
                
                if (0 == point.distance) {
                    // point at scanner or no echo
                    continue;
                }
                ScanPoint xyzd = applyCorrections(point, layerNumber, block.angle);

                // write data to text file
                // write: layerNumber[0-63], X[m], Y[m], Z[m], distance[m], intensity[0-255]
                outputTextFile
                    << layerNumber << " "
                    << xyzd.x << " "
                    << xyzd.y << " "
                    << xyzd.z << " "
                    << xyzd.d << " "
                    << xyzd.i << "\n"
                    ;

                ++pointCountTotal;
                
                //betaRadians += kFieldOfViewRadians; // vertical FOV
            }
            LOG_DEBUG("Scan has: " << pointCountTotal << " valid points");
        }
        
        outputTextFile.close();

        ++counter;
    }
    
    inputDbiteFile.close();
    
    LOG_INFO("Converted " << counter << " Velodyne scans");
}

/// @returns ScanPoint with corrected coordinates and distance in [meters]
VelodyneConverter::ScanPoint VelodyneConverter::applyCorrections(const VelodyneRawPoint & point, unsigned layerNumber, unsigned blockAngleIndex) const
{
    // `blockAngleIndex` equivalent to `data->position`
    //BOOST_ASSERT(data->position < 36000);
    BOOST_ASSERT(blockAngleIndex < 36000);

    // TODO: get scanner position from configuration
    ScanPoint scannerPosition; //< equivalent to `pos` in Velodyne documentation
    // `pos` object holds the current 3D position of the scanner (i.e. from GPS)
    // `pos` is the position of the scanner, factor in rotation angle and horizontal offset
    scannerPosition.x = 0;
    scannerPosition.y = 0;
    scannerPosition.z = 0;

    /// corrected point
    ScanPoint xyzd;
    if (0 == point.distance) {
        // point at scanner or no echo
        xyzd.x = 0;
        xyzd.y = 0;
        xyzd.z = 0;
        xyzd.d = 0;
        xyzd.i = point.intensity;
        return xyzd;
    }

    CalibrationPoint cal = getCalibrationPoint(layerNumber);
    
    // increments by 0.2 cm // TODO: get from correction file <DB>/<distLSB_>
    static const Real distLSB = 0.2f; // 0.2 cm
    
    // Get measured distance, distance1
    Real distance1 = distLSB * static_cast<Real>(point.distance);
    // Corrected distance by distance calibration at 25.04m
    Real distance = distance1 + cal.getDistCorrection();
    
    // Application des corrections du LIDAR (cf. doc velodyne)
    Real cosVertAngle = cal.getCosVertCorrection();
    Real sinVertAngle = cal.getSinVertCorrection();
    Real cosRotCorrection = cal.getCosRotCorrection();
    Real sinRotCorrection = cal.getSinRotCorrection();
    //Real cosRotAngle = rotCosTable[data->position]*cosRotCorrection + rotSinTable[data->position]*sinRotCorrection;
    //Real sinRotAngle = rotSinTable[data->position]*cosRotCorrection - rotCosTable[data->position]*sinRotCorrection;
    Real cosRotAngle = rotCosTable[blockAngleIndex] * cosRotCorrection + rotSinTable[blockAngleIndex] * sinRotCorrection;
    Real sinRotAngle = rotSinTable[blockAngleIndex] * cosRotCorrection - rotCosTable[blockAngleIndex] * sinRotCorrection;
    
    Real hOffsetCorr = cal.getHorizOffsetCorrection() / VLS_DIM_SCALE;
    Real vOffsetCorr = cal.getVertOffsetCorrection() / VLS_DIM_SCALE;

    //Real dxy = xyzd.d * cosVertAngle - vOffsetCorr * sinVertAngle;
    //xyzd.x = dxy * sinRotAngle - hOffsetCorr * cosRotAngle;
    //xyzd.y = dxy * cosRotAngle + hOffsetCorr * sinRotAngle;
    //xyzd.z = xyzd.d * sinVertAngle + vOffsetCorr * cosVertAngle;

    // Convert distance to X-Y plane
    Real xyDistance = distance * cosVertAngle;
    
    // Calculate temporal X, use absolute value. 
    Real xx = xyDistance * sinRotAngle - hOffsetCorr * cosRotAngle + scannerPosition.x;
    xx = abs(xx);
    // Calculate temporal Y, use absolute value 
    Real yy = xyDistance * cosRotAngle + hOffsetCorr * sinRotAngle + scannerPosition.y;
    yy = abs(yy);
    
    // Get 2points calibration values,Linear interpolation to get distance correction for X and Y, that means distance correction use different value at different distance
    // near point calibration at 2.40 m, far point calibration at 25.04 m
    Real distanceCorrX = (cal.getDistCorrection() - cal.getDistCorrectionX()) * (xx - 240) / (2504 - 240) + cal.getDistCorrectionX();
    // near point calibration at 1.93 m, far point calibration at 25.04 m
    Real distanceCorrY = (cal.getDistCorrection() - cal.getDistCorrectionY()) * (yy - 193) / (2504 - 193) + cal.getDistCorrectionY(); //fix in V2.O
    
    // Unit convert: cm converts to meter 
    distance1 /= VLS_DIM_SCALE;
    distanceCorrX /= VLS_DIM_SCALE;
    distanceCorrY /= VLS_DIM_SCALE;

    // Measured distance add distance correction in X. 
    distance = distance1 + distanceCorrX; 
    xyDistance = distance * cosVertAngle; // Convert to X-Y plane
    // Calculate X coordinate
    xyzd.x = xyDistance * sinRotAngle - hOffsetCorr * cosRotAngle + scannerPosition.x / VLS_DIM_SCALE;

    // Measured distance add distance correction in Y.
    distance = distance1 + distanceCorrY;
    xyDistance = distance * cosVertAngle; //Convert to X-Y plane
    // Calculate Y coordinate
    xyzd.y = xyDistance * cosRotAngle + hOffsetCorr * sinRotAngle + scannerPosition.y / VLS_DIM_SCALE;

    //Calculate Z coordinate, formula is : setZ(distance * sinVertAngle + vOffsetCorr 
    xyzd.z = distance * sinVertAngle + vOffsetCorr + scannerPosition.z / VLS_DIM_SCALE;

    // Set distance
    xyzd.d = distance;
    
    /////////////////////////////////////////
    // Correct intensity
    Real intensityScale  =  0; 
    int32_t minIntensity = 0; //db->getMinlntensity(laser); 
    int32_t maxIntensity = 255; //db->getMaxlntensity(laser); 
    // Get intensity scale 
    intensityScale = static_cast<Real>(maxIntensity - minIntensity);

    // Get firing intensity
    xyzd.i = point.intensity;
    // Calculate  offset  according  calibration
    Real focalOffsetTerm = (1 - cal.getFocalDistance()) / 13100;
    Real focalOffset = 256 * focalOffsetTerm * focalOffsetTerm;

    // Get slope from calibration
    Real focalSlope = cal.getFocalSlope();
    
    // Calculate corrected intensity vs distance
    Real intensityTerm = (1 - distance) / 65535;
    xyzd.i = point.intensity + focalSlope * (focalOffset - 256 * intensityTerm * intensityTerm);

    xyzd.i = max(xyzd.i, minIntensity);
    xyzd.i = min(xyzd.i, maxIntensity);

    //// Scale to new intensity scale
    //Real intensityColor = static_cast<Real>((xyzd.i - minIntensity) / intensityScale);
    //// Convert to jet color 
    //int32_t rgb = static_cast<int32_t>(intensityColor * 63);
    ////glColor3f(rcolor[rgb], gcolor[rgb], bcolor[rgb]);

    return xyzd;
}

void VelodyneConverter::loadCorrections(const std::string & filename)
{
    LOG_TRACE(BOOST_CURRENT_FUNCTION);

    /////////////////////////////////////////
    // Read the DOM tree form file
    QFile f(filename.c_str());
    if (!f.open(QIODevice::ReadOnly)) {
        LOG_ERROR("cannot open correction file '" << filename << "'");
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&f)) {
        LOG_ERROR("cannot read XML content of '" << filename << "'");
        f.close();
        return;
    }
    f.close();

    LOG_INFO("parsing XML correction file '" << filename << "'");

    /////////////////////////////////////////
    // Parse the DOM tree
    QDomElement root = doc.documentElement();

    // get <DB>
    QDomElement db = root.elementsByTagName("DB").at(0).toElement();

    // get <points_>
    QDomElement points = db.elementsByTagName("points_").at(0).toElement();
    if (points.isNull()) {
        LOG_WARN("cannot find <points_> tag");
        return;
    }

    int loadedCorrections = 0;
    // get <item>
    QDomNodeList items = points.elementsByTagName("item");
    for (int i = 0, itemsSize = items.size(); i < itemsSize; ++i) {
        QDomElement item = items.at(i).toElement();
        QDomElement px = item.elementsByTagName("px").at(0).toElement();
        if (px.isNull()) {
            LOG_WARN("cannot find <px> tag");
            continue;
        }

        // get <id_>
        QDomElement id = px.elementsByTagName("id_").at(0).toElement();
        if (id.isNull()) {
            LOG_WARN("cannot find <id_> tag");
            continue;
        }
        int layerNumber = id.text().toInt();
        LOG_DEBUG("layerNumber = " << layerNumber);

        // get corrections
        mRotCorrection[layerNumber] = getFirstElementText(px, "rotCorrection_").toDouble();
        mVertCorrection[layerNumber] = getFirstElementText(px, "vertCorrection_").toDouble();
        mDistCorrection[layerNumber] = getFirstElementText(px, "distCorrection_").toDouble();
        mDistCorrectionX[layerNumber] = getFirstElementText(px, "distCorrectionX_").toDouble();
        mDistCorrectionY[layerNumber] = getFirstElementText(px, "distCorrectionY_").toDouble();
        mVertOffsetCorrection[layerNumber] = getFirstElementText(px, "vertOffsetCorrection_").toDouble();
        mHorizOffsetCorrection[layerNumber] = getFirstElementText(px, "horizOffsetCorrection_").toDouble();
        mFocalDistance[layerNumber] = getFirstElementText(px, "focalDistance_").toDouble();
        mFocalSlope[layerNumber] = getFirstElementText(px, "focalSlope_").toDouble();

        ++loadedCorrections;
    }

    LOG_DEBUG("parsed corrections for " << loadedCorrections << " layers");
    LOG_INFO("finished parsing XML correction file '" << filename << "'");
}

QString getFirstElementText(QDomElement & element, const QString tagName)
{
    QString text = element.elementsByTagName(tagName).at(0).toElement().text();
    LOG_TRACE("text = " << text);
    LOG_TRACE("double = " << text.toDouble());
    return text;
}
