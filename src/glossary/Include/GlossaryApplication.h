#pragma once

#include <memory>

#include "Glossary.h"

namespace glossary
{
// TODO: do frontend in qt
class GlossaryApplication
{
public:
    GlossaryApplication();

    void run();

private:
    std::unique_ptr<Glossary> glossary;
};
}