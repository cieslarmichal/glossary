#include "plog/Log.h"

#include "Glossary.h"
#include "utils/GetProjectPath.h"

int main(int, char**)
{
    const auto logFilepath{utils::getProjectPath("glossary") + "glossary_logs"};
    plog::init(plog::debug, "Sample.log");

    LOG_DEBUG << "Hello log!";

    Glossary app;
    app.run();

    return 0;
}
