#include "Glossary.h"

#include "plog/Log.h"

#include "GlossaryApplication.h"
#include "utils/FileAccessImpl.h"
#include "utils/GetSyslogPath.h"
Glossary::Glossary()
    : fileAccess{std::make_shared<utils::FileAccessImpl>("glossary")},
      application{std::make_unique<GlossaryApplication>(fileAccess)}
{
    initializeLogger();
    LOG_DEBUG << "Initializing glossary";
}

Glossary::~Glossary()
{
    LOG_DEBUG << "Shutting down glossary";
}

void Glossary::run()
{
    LOG_DEBUG << "Starting glossary application";
    application->run();
}

void Glossary::initializeLogger() const
{
    const auto resetContent{""};
    fileAccess->write("syslog.log", resetContent);
    plog::init(plog::debug, utils::getSyslogPath().c_str());
}
