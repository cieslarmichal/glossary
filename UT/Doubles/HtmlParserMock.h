#pragma once

#include "gmock/gmock.h"

#include "HtmlParser.h"

class HtmlParserMock : public HtmlParser
{
public:
    MOCK_CONST_METHOD1(parse, std::vector<std::string>(const std::string &));
};
