#ifndef SPANCPTCONVERTER_H
#define SPANCPTCONVERTER_H

#include "DbiteConverter.h"

namespace pacpus {

class DbiteFile;

class SpanCptConverter
    : public DbiteConverter
{
public:
    SpanCptConverter();
    virtual ~SpanCptConverter();

    virtual void convert(const std::string & inputFilePath) const;

private:
    void convertBestgpsposa(std::ofstream & outputTextFile, pacpus::DbiteFile & inputDbiteFile) const;
    void convertRawimusa(std::ofstream & outputTextFile, pacpus::DbiteFile & inputDbiteFile) const;
    void convertInspvaa(std::ofstream & outputTextFile, pacpus::DbiteFile & inputDbiteFile) const;
    void convertInscov(std::ofstream & outputTextFile, pacpus::DbiteFile & inputDbiteFile) const;
};

} // namespace pacpus

#endif // SPANCPTCONVERTER_H
