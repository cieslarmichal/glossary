#pragma once

#include <memory>

#include "Application.h"
#include "utils/FileAccess.h"

// TODO: logs
// TODO: QT maybe in future
// TODO: filepaths with filesystem
// TODO: probabilty
// TODO: try to get rid of std::cin from class

class Glossary
{
public:
    Glossary();
    ~Glossary();

    void run();

private:
    void initializeLogger() const;

    std::shared_ptr<utils::FileAccess> fileAccess;
    std::unique_ptr<Application> application;
};