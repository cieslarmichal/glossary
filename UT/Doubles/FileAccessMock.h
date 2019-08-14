#pragma once

#include "gmock/gmock.h"

#include "FileAccess.h"

class FileAccessMock : FileAccess
{
public:
    MOCK_CONST_METHOD2(write, void(const std::string &, const std::string &));
    MOCK_CONST_METHOD2(append, void(const std::string &, const std::string &));
    MOCK_CONST_METHOD1(readContent, void(const std::string &));
};