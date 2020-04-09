#pragma once

#include "GlossaryFactory.h"

namespace glossary
{
class DefaultGlossaryFactory : public GlossaryFactory
{
public:
    std::unique_ptr<Glossary> createGlossary() const override;
};
}