#pragma once

#include "Application.h"
#include <memory>

//TODO: logs
//TODO: QT maybe in future
//TODO: filepaths with filesystem
//TODO: probabilty
//TODO: add inserting only polish or english word and downloading other one
//TODO: check every function for tests

class Glossary
{
public:
    Glossary();

    void run();

private:
    std::unique_ptr<Application> application;
};