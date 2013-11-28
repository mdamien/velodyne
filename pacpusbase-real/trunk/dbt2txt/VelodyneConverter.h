#ifndef VELODYNECONVERTER_H
#define VELODYNECONVERTER_H

#include <boost/array.hpp>

#include "kernel/cstdint.h"

#include "DbiteConverter.h"

class CalibrationPoint;
struct VelodyneRawPoint;

namespace pacpus {

/// @see http://velodynelidar.com/lidar/products/manual/63-HDL64ES2h%20HDL-64E%20S2%20CD%20HDL-64E%20S2%20Users%20Manual.pdf
class VelodyneConverter
    : public DbiteConverter
{
public:
    VelodyneConverter();
    virtual ~VelodyneConverter();

    virtual void convert(const std::string & inputFilePath) const;

private:
    typedef float Real;
    struct ScanPoint;

    /// @param blockAngleIndex azimuth in 100th of degrees [0-35999]
    ScanPoint applyCorrections(const VelodyneRawPoint & point, unsigned layerNumber, unsigned blockAngleIndex) const;
    void loadCorrections(const std::string & filename);

    static const unsigned kVelodyneLayerCount = 64;

    CalibrationPoint getCalibrationPoint(unsigned laserNumber) const;
    boost::array<Real, kVelodyneLayerCount>
        mRotCorrection,
        mVertCorrection,
        mDistCorrection,
        mDistCorrectionX,
        mDistCorrectionY,
        mVertOffsetCorrection,
        mHorizOffsetCorrection,
        mFocalDistance,
        mFocalSlope;

    boost::array<Real, 360*100>
        rotCosTable,
        rotSinTable;
};

} // namespace pacpus

#endif // VELODYNECONVERTER_H
