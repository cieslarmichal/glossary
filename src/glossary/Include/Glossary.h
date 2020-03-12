#pragma once

#include <memory>

#include "Application.h"
#include "utils/FileAccess.h"

// TODO: QT maybe in future
// TODO: filepaths with filesystem
// TODO: probabilty

class Glossary
{
public:
    Glossary();

    void run();

private:
    std::shared_ptr<utils::FileAccess> fileAccess;
    std::unique_ptr<Application> application;
};