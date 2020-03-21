#include "DefaultFileAccessFactory.h"

#include "DefaultFileAccess.h"
#include "ProjectFileAccess.h"

namespace utils
{
std::unique_ptr<FileAccess> DefaultFileAccessFactory::createDefaultFileAccess() const
{
    return std::make_unique<DefaultFileAccess>();
}

std::unique_ptr<FileAccess>
DefaultFileAccessFactory::createProjectFileAccess(const std::string& projectName) const
{
    return std::make_unique<ProjectFileAccess>(projectName);
}
}