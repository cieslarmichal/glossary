#include "GetProjectPath.h"

#include "GetExecutablePath.h"
#include "collection/StringHelper.h"
#include "exceptions/FileNotFound.h"

namespace common::fileSystem
{
namespace
{
constexpr auto fileNotFoundMessage{"Project directory not found in path: "};
}

std::string getProjectPath(const std::string& projectName)
{
    const std::string currentPath = getExecutablePath();

    const auto projectNamePosition = currentPath.find(projectName);

    if (projectNamePosition == std::string::npos)
    {
        throw exceptions::FileNotFound{fileNotFoundMessage + currentPath};
    }

    auto projectPath =
        common::collection::substring(currentPath, 0, projectNamePosition + projectName.length() + 1);

    return projectPath;
}
}