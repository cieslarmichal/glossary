#pragma once

#include "ApplicationFactory.h"

namespace glossary
{
class GlossaryApplicationFactory : public ApplicationFactory
{
public:
    std::unique_ptr<Application> createApplication() const override;
};
}