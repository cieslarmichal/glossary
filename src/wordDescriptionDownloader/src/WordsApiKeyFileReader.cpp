#include "WordsApiKeyFileReader.h"

#include <iostream>

#include "utils/GetProjectPath.h"

namespace glossary::wordDescriptionDownloader
{

const std::string WordsApiKeyFileReader::filePathContainingPathToFileWithApiKey{
    utils::getProjectPath("glossary") + "config/wordsApiKeyLocation.txt"};

WordsApiKeyFileReader::WordsApiKeyFileReader(std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

boost::optional<std::string> WordsApiKeyFileReader::readApiKey() const
{
    if (const auto filePathWithApiKey = readPathToFileWithApiKey())
    {
        if (const auto fileContentWithApiKey = readApiKeyFromFile(*filePathWithApiKey))
            return apiKeyFileFormatter.getFormattedApiKey(*fileContentWithApiKey);
    }
    return boost::none;
}

boost::optional<std::string> WordsApiKeyFileReader::readPathToFileWithApiKey() const
{
    if (not fileAccess->exists(filePathContainingPathToFileWithApiKey))
    {
        std::cerr << "Config file does not exist: " << filePathContainingPathToFileWithApiKey;
        return boost::none;
    }
    return fileAccess->readContent(filePathContainingPathToFileWithApiKey);
}

boost::optional<std::string>
WordsApiKeyFileReader::readApiKeyFromFile(const std::string& filePathWithApiKey) const
{
    if (not fileAccess->exists(filePathWithApiKey))
    {
        std::cerr << "File from config file: " << filePathContainingPathToFileWithApiKey
                  << " does not exist: " << filePathWithApiKey;
        return boost::none;
    }
    return fileAccess->readContent(filePathWithApiKey);
}

}