#pragma once

#include <memory>

#include "FileAccess.h"
#include "TranslationsMemoryStorage.h"
#include "TranslationsStorage.h"
#include "wordsDb/translationsDb/TranslationsSerializer.h"

namespace wordsDb::translationsDb
{
class TranslationsPersistentStorage : public TranslationsStorage
{
public:
    TranslationsPersistentStorage(
        std::shared_ptr<const FileAccess>,
        std::shared_ptr<const TranslationsSerializer>);

    void addTranslation(Translation) override;
    boost::optional<Translation>
    getTranslation(const PolishWord&) const override;
    Translations getTranslations() const override;
    bool contains(const PolishWord&) const override;
    Translations::size_type size() const override;
    bool empty() const override;
    Translations::const_iterator begin() const override;
    Translations::const_iterator end() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const TranslationsSerializer> serializer;
    TranslationsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}