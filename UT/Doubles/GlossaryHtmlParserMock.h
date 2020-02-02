#pragma once

#include "gmock/gmock.h"

#include "GlossaryHtmlParser.h"

class GlossaryHtmlParserMock : public GlossaryHtmlParser
{
public:
    MOCK_CONST_METHOD1(parse, std::vector<std::string>(const std::string&));
};
