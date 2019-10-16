#pragma once

#include "Application.h"
#include <memory>

//TODO: logs
//TODO: QT maybe in future
//TODO: filepaths with filesystem
//TODO: probabilty

class Glossary
{
public:
    Glossary();

    void run();

private:
    std::unique_ptr<Application> application;
};