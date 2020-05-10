#pragma once

#include <memory>

#include "Glossary.h"

namespace glossary
{
class GlossaryApplication
{
public:
    GlossaryApplication();

    void run();

private:
    std::unique_ptr<Glossary> glossary;
};
}