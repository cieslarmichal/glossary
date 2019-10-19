#include "Glossary.h"

#include "GlossaryApplication.h"

Glossary::Glossary() : application{std::make_unique<GlossaryApplication>()}
{
}

void Glossary::run()
{
    application->run();
}
