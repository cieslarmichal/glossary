#pragma once

#include "gmock/gmock.h"

#include "LinesSelector.h"

namespace glossary::wordDescriptionDownloader
{
class LinesSelectorMock : public LinesSelector
{
public:
    MOCK_CONST_METHOD1(selectLines, std::vector<std::string>(const std::string&));
};
}