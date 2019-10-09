#pragma once

#include "gmock/gmock.h"

#include "FileAccess.h"

class FileAccessMock : public FileAccess
{
public:
    MOCK_CONST_METHOD2(write, void(const std::string &, const std::string &));
    MOCK_CONST_METHOD2(append, void(const std::string &, const std::string &));
    MOCK_CONST_METHOD1(readContent, std::string(const std::string &));
};
