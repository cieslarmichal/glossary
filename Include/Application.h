#pragma once

class Application
{
public:
    //TODO: if There are no wordsDescriptions stored, wypierdala apke
    virtual ~Application() = default;

    virtual void run() = 0;
};
