#include "FilenamePathFilter.h"

namespace utils
{

namespace
{
const std::string delimiter = R"(/)";
}

ListOfFiles FilenamePathFilter::filter(const ListOfFiles& filepaths) const
{
    std::vector<std::string> filenames;
    for (const auto& filepath : filepaths)
    {
        filenames.emplace_back(getFilename(filepath));
    }
    return filenames;
}

std::string FilenamePathFilter::getFilename(const std::string& filepath) const
{
    const auto lastDelimiterPosition = filepath.rfind(delimiter);
    if (lastDelimiterPosition != std::string::npos && filepath.size() + 1 > lastDelimiterPosition)
    {
        return filepath.substr(lastDelimiterPosition + 1);
    }
    return filepath;
}

}