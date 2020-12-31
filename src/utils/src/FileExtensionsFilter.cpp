#include "FileExtensionsFilter.h"

#include <filesystem>

#include <boost/algorithm/cxx11/any_of.hpp>

namespace fs = std::filesystem;

namespace utils
{
FilePaths FileExtensionsFilter::filterByExtensions(const FilePaths& listOfFiles,
                                                   const std::vector<std::string>& extensions) const
{
    FilePaths filteredFilePaths;

    for (const auto& filename : listOfFiles)
    {
        if (containsAnyOfExtensions(filename, extensions))
        {
            filteredFilePaths.push_back(filename);
        }
    }

    if (filteredFilePaths.empty())
    {
        return listOfFiles;
    }
    return filteredFilePaths;
}

bool FileExtensionsFilter::containsAnyOfExtensions(const fs::path& filename,
                                                   const std::vector<std::string>& extensions) const
{
    return boost::algorithm::any_of(extensions,
                                    [&](const auto& extension) { return filename.extension() == extension; });
}
}