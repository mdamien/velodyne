#ifndef DBITECONVERTER_H
#define DBITECONVERTER_H

#include <string>

namespace pacpus {

class DbiteConverter
{
public:
    DbiteConverter();
    virtual ~DbiteConverter();

    /// Abstract method.
    /// Converts Dbite file into text file(s).
    ///
    /// Outputs written to the string given by getOutputDirectory().
    /// @param inputFilePath path to input Dbite file
    virtual void convert(const std::string & inputFilePath) const = 0;

    const std::string & getOutputDirectory() const;
    void setOutputDirectory(const std::string & outputDirectory);

    static bool createPath(const std::string & path);
    static char getPathSeparator();
    static std::string getBasename(const std::string & filePath);
    static std::string getDirname(const std::string & filePath);
    static std::string getFilename(const std::string & filePath);
    static std::string getCompleteBasename(const std::string & filePath);
    static std::string getCompleteSuffix(const std::string & filePath);

private:
    std::string mOutputDirectory;
};

} // namespace pacpus

#endif // DBITECONVERTER_H
