#pragma once

#include <memory>
#include "view/MainView.h"

class MainViewCreator
{
public:
    MainViewCreator() = delete;

    static std::unique_ptr<MainView> createMainView();
};

