#pragma once

#include <memory>

#include "Application.h"

// TODO: logs
// TODO: QT maybe in future
// TODO: filepaths with filesystem
// TODO: probabilty
// TODO: add inserting only polish or english word and downloading other one
// TODO: check every function for tests
// TODO: add testability to WordsGeneratorService
// TODO: add testability to GlossaryApplication
// TODO: try to get rid of std::cin from class

class Glossary
{
public:
    Glossary();

    void run();

private:
    std::unique_ptr<Application> application;
};