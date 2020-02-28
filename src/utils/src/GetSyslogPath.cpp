#include "GetSyslogPath.h"

#include "GetProjectPath.h"

namespace utils
{
std::string getSyslogPath()
{
    const auto projectName{"glossary"};
    const auto projectPath = getProjectPath(projectName);
    return projectPath + "syslog.log";
}
}