#include "DbiteConverter.h"

#include <QDir>
#include <QFileInfo>

using namespace pacpus;

DbiteConverter::DbiteConverter()
{
}

DbiteConverter::~DbiteConverter()
{
}

const std::string & DbiteConverter::getOutputDirectory() const
{
    return mOutputDirectory;
}

bool DbiteConverter::createPath(const std::string & path)
{
    QDir dir;
    return dir.mkpath(path.c_str());
}

char DbiteConverter::getPathSeparator()
{
    return QDir::separator().toAscii();
}

void DbiteConverter::setOutputDirectory(const std::string & outputDirectory)
{
    mOutputDirectory = outputDirectory;
}

std::string DbiteConverter::getBasename(const std::string & filePath)
{
    QFileInfo fi(filePath.c_str());
    return fi.baseName().toStdString();
}

std::string DbiteConverter::getDirname(const std::string & filePath)
{
    QFileInfo fi(filePath.c_str());
    QDir dir = fi.absoluteDir();
    return dir.path().toStdString();
}

std::string DbiteConverter::getFilename(const std::string & filePath)
{
    QFileInfo fi(filePath.c_str());
    return fi.fileName().toStdString();
}

std::string DbiteConverter::getCompleteBasename(const std::string & filePath)
{
    QFileInfo fi(filePath.c_str());
    return fi.completeBaseName().toStdString();
}

std::string DbiteConverter::getCompleteSuffix(const std::string & filePath)
{
    QFileInfo fi(filePath.c_str());
    return fi.completeSuffix().toStdString();
}
