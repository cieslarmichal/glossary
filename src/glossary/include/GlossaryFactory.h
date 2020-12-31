#pragma once

#include <memory>

#include "Glossary.h"
#include "GlossaryApi.h"

namespace glossary
{
class GLOSSARY_API GlossaryFactory
{
public:
    virtual ~GlossaryFactory() = default;

    virtual std::unique_ptr<Glossary> createGlossary() const = 0;

    static std::unique_ptr<GlossaryFactory> createGlossaryFactory();
};
}