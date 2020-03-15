#pragma once

#include "gmock/gmock.h"

#include "FileAccess.h"

namespace utils
{
class FileAccessMock : public FileAccess
{
public:
    MOCK_CONST_METHOD2(write, void(const std::string&, const std::string&));
    MOCK_CONST_METHOD2(append, void(const std::string&, const std::string&));
    MOCK_CONST_METHOD1(readContent, std::string(const std::string&));
    MOCK_CONST_METHOD1(createDirectory, void(const std::string&));
    MOCK_CONST_METHOD1(remove, void(const std::string&));
    MOCK_CONST_METHOD2(rename, void(const std::string&, const std::string&));
    MOCK_CONST_METHOD1(exists, bool(const std::string&));
    MOCK_CONST_METHOD1(isRegularFile, bool(const std::string&));
    MOCK_CONST_METHOD1(isDirectory, bool(const std::string&));
    MOCK_CONST_METHOD1(getAllPathsFromDirectory, std::vector<std::string>(const std::string&));
    MOCK_CONST_METHOD2(getAllFilenamesFromDirectory,
                       std::vector<std::string>(const std::string&, const std::vector<std::string>&));
};
}