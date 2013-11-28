#ifndef ALASCACONVERTER_H
#define ALASCACONVERTER_H

#include "DbiteConverter.h"

namespace pacpus {

class AlascaConverter
    : public DbiteConverter
{
public:
    virtual void convert(const std::string & inputFilePath) const;
};

} // namespace pacpus

#endif // ALASCACONVERTER_H
