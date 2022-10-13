#include "TranslationsPersistentStorage.h"

#include <iostream>

#include "../../../common/fileSystem/include/GetProjectPath.h"
#include "utils/exceptions/FileNotFound.h"

namespace glossary::translation
{
const std::string TranslationsPersistentStorage::directory{common::getProjectPath("glossary") +
                                                           "repositoryFiles/"};
const std::string TranslationsPersistentStorage::filename{directory + "translations.txt"};

TranslationsPersistentStorage::TranslationsPersistentStorage(
    std::shared_ptr<const common::FileAccess> fileAccessInit,
    std::shared_ptr<const TranslationsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}
{
    loadFile();
}

void TranslationsPersistentStorage::addTranslation(Translation translation)
{
    if (not storage.contains(translation.sourceText))
    {
        storage.addTranslation(std::move(translation));
        serialize();
    }
}

std::optional<Translation> TranslationsPersistentStorage::getTranslation(const std::string& polishWord) const
{
    return storage.getTranslation(polishWord);
}

std::vector<Translation> TranslationsPersistentStorage::getTranslations() const
{
    return storage.getTranslations();
}

bool TranslationsPersistentStorage::contains(const std::string& polishWord) const
{
    return storage.contains(polishWord);
}

std::vector<Translation>::size_type TranslationsPersistentStorage::size() const
{
    return storage.size();
}

bool TranslationsPersistentStorage::empty() const
{
    return storage.empty();
}

void TranslationsPersistentStorage::loadFile()
{
    std::vector<Translation> translations;

    try
    {
        translations = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const common::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while deserializing translations " << e.what();
        return;
    }

    for (const auto& translation : translations)
    {
        storage.addTranslation(translation);
    }
}

void TranslationsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(filename, serializer->serialize(storage.getTranslations()));
    }
    catch (const common::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing translations " << e.what();
    }
}

}
