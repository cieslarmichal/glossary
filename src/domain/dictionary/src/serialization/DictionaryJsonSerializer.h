#pragma once

#include "nlohmann/json.hpp"

#include "DictionarySerializer.h"

namespace glossary::dictionary::serialization
{
class DictionaryJsonSerializer : public DictionarySerializer
{
public:
    std::string serialize(const Dictionaries&) const override;
    Dictionaries deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromDictionary(const Dictionary&) const;
    nlohmann::json getJsonFromDictionaryWords(const std::vector<DictionaryWord>&) const;
    nlohmann::json getJsonFromDictionaryWord(const DictionaryWord&) const;
    Dictionaries getDictionariesFromJson(const nlohmann::json&) const;
    Dictionary getDictionaryFromJson(const nlohmann::json&) const;
    std::vector<DictionaryWord> getDictionaryWordsFromJson(const nlohmann::json&) const;
    DictionaryWord getDictionaryWordFromJson(const nlohmann::json&) const;
    bool isDictionaryValid(const nlohmann::json&) const;
    bool isDictionaryWordValid(const nlohmann::json&) const;
};
}
