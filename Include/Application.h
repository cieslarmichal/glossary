#pragma once

class Application
{
public:
    //TODO: if There are html content reading wypierdala apke

    virtual ~Application() = default;

    virtual void run() = 0;
};
