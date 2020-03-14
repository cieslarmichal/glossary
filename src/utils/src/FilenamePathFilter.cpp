#include "FilenamePathFilter.h"

#include <iostream>

namespace utils
{

namespace fs = std::experimental::filesystem;

ListOfFiles FilenamePathFilter::filter(const ListOfFiles& filepaths) const
{
    std::vector<std::string> filenames;
    for (const auto& filepath : filepaths)
    {
        if(const auto filename = getFilename(filepath))
        {
            filenames.emplace_back(*filename);
        }
    }
    return filenames;
}

boost::optional<std::string> FilenamePathFilter::getFilename(const std::string& path) const
{
    const auto filepath = fs::path{path};
    if(isFile(filepath))
    {
        return static_cast<std::string>(filepath.filename());
    }
    return boost::none;
}

bool FilenamePathFilter::isFile(const std::experimental::filesystem::path& path) const
{
    return fs::is_regular_file(path);
}

}