#pragma once

#include <memory>

#include "Application.h"

namespace glossary
{
class ApplicationFactory
{
public:
    virtual ~ApplicationFactory() = default;

    virtual std::unique_ptr<Application> createApplication() const = 0;

    static std::unique_ptr<ApplicationFactory> createApplicationFactory();
};
}