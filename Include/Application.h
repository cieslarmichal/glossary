#pragma once

class Application
{
public:
    virtual ~Application() = default;

    virtual void run() = 0;
};
