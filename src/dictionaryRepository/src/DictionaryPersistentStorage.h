#pragma once

#include <memory>

#include "DictionaryMemoryStorage.h"
#include "DictionarySerializer.h"
#include "DictionaryStorage.h"
#include "utils/FileAccess.h"

namespace glossary::dictionaryRepository
{
class DictionaryPersistentStorage : public DictionaryStorage
{
public:
    DictionaryPersistentStorage(std::shared_ptr<const utils::FileAccess>,
                                std::shared_ptr<const DictionarySerializer>);

    void addDictionary(const DictionaryName&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string& englishWord, const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;
    Dictionaries::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
    std::shared_ptr<const DictionarySerializer> serializer;
    DictionaryMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
