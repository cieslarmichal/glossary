#pragma once

namespace glossary
{
class ConnectionChecker
{
public:
    virtual ~ConnectionChecker() = default;

    virtual bool connectionAvailable() const = 0;
};
}