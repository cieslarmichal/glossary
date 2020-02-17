#pragma once

class Application
{
public:
    // TODO: add scripts to build targets and run UTs.
    virtual ~Application() = default;

    virtual void run() = 0;
};
