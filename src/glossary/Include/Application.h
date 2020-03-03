#pragma once

class Application
{
public:
    // change names with Impl in it
    // add logs in each file
    // remove fileaccessimpl from include

    virtual ~Application() = default;

    virtual void run() = 0;
};
