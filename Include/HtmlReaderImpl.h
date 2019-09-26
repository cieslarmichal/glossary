#pragma once

#include "HtmlReader.h"

#include <stdexcept>

class HtmlReaderImpl : public HtmlReader
{
public:
    std::string read(const std::string &) const override;
};


