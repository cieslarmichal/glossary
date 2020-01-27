#pragma once

#include <memory>

#include "FileAccess.h"
#include "WordsDescriptionsMemoryStorage.h"
#include "WordsDescriptionsSerializer.h"
#include "WordsDescriptionsStorage.h"

namespace wordsDb::wordsDescriptionsDb
{

class WordsDescriptionsPersistentStorage : public WordsDescriptionsStorage
{
public:
    WordsDescriptionsPersistentStorage(
        std::shared_ptr<const FileAccess>,
        std::shared_ptr<const WordsDescriptionsSerializer>);

    void addWordDescription(const WordDescription&) override;
    boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;
    WordsDescriptions::const_iterator begin() const override;
    WordsDescriptions::const_iterator end() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const WordsDescriptionsSerializer> serializer;
    WordsDescriptionsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
