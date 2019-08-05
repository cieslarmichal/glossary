#pragma once

#include "HtmlReader.h"

#include <stdexcept>

class HtmlReaderImpl : public HtmlReader
{
public:
    struct ConnectionFailed : std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    std::string read(const std::string &) const override;
};


