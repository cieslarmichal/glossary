#pragma once

#include <stdexcept>

#include "HtmlReader.h"

class HtmlReaderImpl : public HtmlReader
{
public:
    std::string read(const std::string&) const override;
};
