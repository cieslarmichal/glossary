#pragma once

#include "WordsSerializer.h"
#include "WordDescriptionSerializer.h"
#include "nlohmann/json.hpp"

class WordsSerializerImpl : public WordsSerializer
{
public:
    std::string serialize(const Words&) const override;
    Words deserialize(const std::string&) const override;

private:
    nlohmann::json getJsonFromWord(const Word&) const;
    Words readWords(const nlohmann::json&) const;
    Words parseWords(const nlohmann::json&) const;
    bool isWordValid(const nlohmann::json&) const;

    WordDescriptionSerializer wordDescriptionSerializer;
};
