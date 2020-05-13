#pragma once

#include "ConnectionStatus.h"

namespace glossary
{
class ConnectionChecker
{
public:
    virtual ~ConnectionChecker() = default;

    virtual ConnectionStatus connectionAvailable() const = 0;
};
}