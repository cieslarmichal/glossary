#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "TranslationsMemoryStorage.h"
#include "TranslationsSerializer.h"
#include "TranslationsStorage.h"

namespace glossary::translation
{
class TranslationsPersistentStorage : public TranslationsStorage
{
public:
    TranslationsPersistentStorage(std::shared_ptr<const common::FileAccess>,
                                  std::shared_ptr<const TranslationsSerializer>);

    void addTranslation(Translation) override;
    std::optional<Translation> getTranslation(const std::string&) const override;
    std::vector<Translation> getTranslations() const override;
    bool contains(const std::string&) const override;
    std::vector<Translation>::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::FileAccess> fileAccess;
    std::shared_ptr<const TranslationsSerializer> serializer;
    TranslationsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}