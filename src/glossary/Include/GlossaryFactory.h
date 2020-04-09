#pragma once

#include <memory>

#include "Glossary.h"

namespace glossary
{
class GlossaryFactory
{
public:
    virtual ~GlossaryFactory() = default;

    virtual std::unique_ptr<Glossary> createGlossary() const = 0;

    static std::unique_ptr<GlossaryFactory> createGlossaryFactory();
};
}