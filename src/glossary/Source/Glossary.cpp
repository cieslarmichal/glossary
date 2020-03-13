#include "Glossary.h"

#include "../../utils/src/FileAccessImpl.h"
#include "GlossaryApplication.h"

Glossary::Glossary()
    : fileAccess{std::make_shared<utils::FileAccessImpl>("glossary")},
      application{std::make_unique<GlossaryApplication>(fileAccess)}
{
}

void Glossary::run()
{
    application->run();
}