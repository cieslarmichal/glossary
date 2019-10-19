#pragma once

#include "gmock/gmock.h"

#include "HtmlReader.h"

class HtmlReaderMock : public HtmlReader
{
public:
    MOCK_CONST_METHOD1(read, std::string(const std::string&));
};
