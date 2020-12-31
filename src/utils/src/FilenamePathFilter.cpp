#include "FilenamePathFilter.h"

namespace utils
{

FilePaths FilenamePathFilter::filterFilenames(const FilePaths& filePaths) const
{
    std::vector<std::string> filenames;
    for (const auto& filepath : filePaths)
    {
        if (const auto filename = getFilename(filepath))
        {
            filenames.emplace_back(*filename);
        }
    }
    return filenames;
}

boost::optional<std::string> FilenamePathFilter::getFilename(const fs::path& filePath) const
{
    if (isFile(filePath))
    {
        return filePath.filename().string();
    }
    return boost::none;
}

bool FilenamePathFilter::isFile(const std::filesystem::path& path) const
{
    return fs::is_regular_file(path);
}

}