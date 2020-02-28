#pragma once

class Application
{
public:
    // change names with Impl in it
    virtual ~Application() = default;

    virtual void run() = 0;
};
