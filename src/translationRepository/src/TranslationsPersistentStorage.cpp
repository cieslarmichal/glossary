#include "TranslationsPersistentStorage.h"

#include <iostream>

#include "utils/exceptions/FileNotFound.h"
#include "utils/GetProjectPath.h"

namespace translationRepository
{

const std::string TranslationsPersistentStorage::directory{utils::getProjectPath("glossary") + "database/"};
const std::string TranslationsPersistentStorage::filename{directory + "translations.txt"};

TranslationsPersistentStorage::TranslationsPersistentStorage(
    std::shared_ptr<const utils::FileAccess> fileAccessInit,
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

boost::optional<Translation> TranslationsPersistentStorage::getTranslation(const SourceText& polishWord) const
{
    return storage.getTranslation(polishWord);
}

Translations TranslationsPersistentStorage::getTranslations() const
{
    return storage.getTranslations();
}

bool TranslationsPersistentStorage::contains(const SourceText& polishWord) const
{
    return storage.contains(polishWord);
}

Translations::size_type TranslationsPersistentStorage::size() const
{
    return storage.size();
}

bool TranslationsPersistentStorage::empty() const
{
    return storage.empty();
}

void TranslationsPersistentStorage::loadFile()
{
    Translations translations;
    try
    {
        translations = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const utils::exceptions::FileNotFound& e)
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
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing translations " << e.what();
    }
}

}
