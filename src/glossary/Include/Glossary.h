#pragma once

#include <memory>

#include "Application.h"

// TODO: QT maybe in future
// TODO: probabilty

class Glossary
{
public:
    Glossary();

    void run();

private:
    std::unique_ptr<Application> application;
};