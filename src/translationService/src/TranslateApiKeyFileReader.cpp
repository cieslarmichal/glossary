#include "TranslateApiKeyFileReader.h"

#include <iostream>

#include "utils/GetProjectPath.h"

namespace glossary::translationService
{

const std::string TranslateApiKeyFileReader::filePathWithPathToFileWithApiKey{
    utils::getProjectPath("glossary") + "config/translatorApiKeyLocation.txt"};

TranslateApiKeyFileReader::TranslateApiKeyFileReader(std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

boost::optional<std::string> TranslateApiKeyFileReader::readApiKey() const
{
    if (const auto filePathWithApiKey = readPathToFileWithApiKey())
    {
        if (const auto fileContentWithApiKey = readApiKeyFromFile(*filePathWithApiKey))
            return apiKeyFromFileContentRetriever.retrieveApiKeyFromFileContent(*fileContentWithApiKey);
    }
    return boost::none;
}

boost::optional<std::string> TranslateApiKeyFileReader::readPathToFileWithApiKey() const
{
    if (not fileAccess->exists(filePathWithPathToFileWithApiKey))
    {
        std::cerr << "Config file does not exist: " << filePathWithPathToFileWithApiKey;
        return boost::none;
    }
    return fileAccess->readContent(filePathWithPathToFileWithApiKey);
}

boost::optional<std::string>
TranslateApiKeyFileReader::readApiKeyFromFile(const std::string& filePathWithApiKey) const
{
    if (not fileAccess->exists(filePathWithApiKey))
    {
        std::cerr << "File from config file: " << filePathWithPathToFileWithApiKey
                  << " does not exist: " << filePathWithApiKey;
        return boost::none;
    }
    return fileAccess->readContent(filePathWithApiKey);
}

}