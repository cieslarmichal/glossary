#pragma once

#include <memory>

#include "Application.h"

namespace glossary
{
// TODO: do frontend in qt
class Glossary
{
public:
    Glossary();

    void run();

private:
    std::unique_ptr<Application> application;
};
}