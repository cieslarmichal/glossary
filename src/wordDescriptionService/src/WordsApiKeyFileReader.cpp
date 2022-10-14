#include "WordsApiKeyFileReader.h"

#include <iostream>

#include "../../common/fileSystem/include/GetProjectPath.h"

namespace glossary::wordDescriptionService
{

const std::string WordsApiKeyFileReader::filePathContainingPathToFileWithApiKey{
    common::fileSystem::getProjectPath("glossary") + "config/wordsApiKeyLocation.txt"};

WordsApiKeyFileReader::WordsApiKeyFileReader(
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::optional<std::string> WordsApiKeyFileReader::readApiKey() const
{
    if (const auto filePathWithApiKey = readPathToFileWithApiKey())
    {
        if (const auto fileContentWithApiKey = readApiKeyFromFile(*filePathWithApiKey))
        {
            return apiKeyFileFormatter.getFormattedApiKey(*fileContentWithApiKey);
        }
    }
    return std::nullopt;
}

std::optional<std::string> WordsApiKeyFileReader::readPathToFileWithApiKey() const
{
    if (not fileAccess->exists(filePathContainingPathToFileWithApiKey))
    {
        std::cerr << "Config file does not exist: " << filePathContainingPathToFileWithApiKey;
        return std::nullopt;
    }
    return fileAccess->readContent(filePathContainingPathToFileWithApiKey);
}

std::optional<std::string>
WordsApiKeyFileReader::readApiKeyFromFile(const std::string& filePathWithApiKey) const
{
    if (not fileAccess->exists(filePathWithApiKey))
    {
        std::cerr << "File from config file: " << filePathContainingPathToFileWithApiKey
                  << " does not exist: " << filePathWithApiKey;
        return std::nullopt;
    }
    return fileAccess->readContent(filePathWithApiKey);
}

}