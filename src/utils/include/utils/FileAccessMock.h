#pragma once

#include "gmock/gmock.h"

#include "FileAccess.h"

namespace utils
{
class FileAccessMock : public FileAccess
{
public:
    MOCK_CONST_METHOD2(write, void(const std::string& filepath, const std::string& content));
    MOCK_CONST_METHOD2(append, void(const std::string& filepath, const std::string& content));
    MOCK_CONST_METHOD1(readContent, std::string(const std::string& filepath));
    MOCK_CONST_METHOD1(createDirectory, void(const std::string& directoryPath));
    MOCK_CONST_METHOD1(remove, void(const std::string& path));
    MOCK_CONST_METHOD2(rename, void(const std::string& oldPath, const std::string& newPath));
    MOCK_CONST_METHOD1(exists, bool(const std::string& path));
    MOCK_CONST_METHOD1(isRegularFile, bool(const std::string& path));
    MOCK_CONST_METHOD1(isDirectory, bool(const std::string& path));
    MOCK_CONST_METHOD1(getAllPathsFromDirectory, std::vector<std::string>(const std::string& directoryPath));
    MOCK_CONST_METHOD1(getAllFilenamesFromDirectory,
                       std::vector<std::string>(const std::string& directoryPath));
    MOCK_CONST_METHOD2(getFilteredFilenamesFromDirectory,
                       std::vector<std::string>(const std::string& directoryPath,
                                                const std::vector<std::string>& extensions));
};
}