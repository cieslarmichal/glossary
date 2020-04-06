#include "Glossary.h"

#include "ApplicationFactory.h"

namespace glossary
{
Glossary::Glossary() : application{ApplicationFactory::createApplicationFactory()->createApplication()} {}

void Glossary::run()
{
    application->run();
}
}