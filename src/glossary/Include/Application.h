#pragma once

namespace glossary
{
class Application
{
public:
    virtual ~Application() = default;

    virtual void run() = 0;
};
}