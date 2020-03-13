#include "FileExtensionsFilter.h"

#include "boost/algorithm/cxx11/any_of.hpp"
#include "boost/algorithm/string/predicate.hpp"

namespace utils
{
ListOfFiles FileExtensionsFilter::filter(const ListOfFiles& listOfFiles,
                                         const std::vector<std::string>& extensions) const
{
    ListOfFiles filteredFiles;

    for (const auto& filename : listOfFiles)
    {
        if (isAnyOfExtensions(filename, extensions))
        {
            filteredFiles.push_back(filename);
        }
    }

    if (filteredFiles.empty())
    {
        return listOfFiles;
    }
    return filteredFiles;
}

bool FileExtensionsFilter::isAnyOfExtensions(const std::string& filename,
                                             const std::vector<std::string>& extensions) const
{
    return boost::algorithm::any_of(
        extensions, [&](const auto& extension) { return boost::algorithm::ends_with(filename, extension); });
}
}