#include "WordsSerializerImpl.h"
#include "nlohmann/json.hpp"

namespace
{

nlohmann::json getJsonFromWord(const Word& word);

const auto specialCharacter = "~";
const std::string newLine = "\n";
const auto openBraces = "{";
const auto closeBraces = "}";
}

std::string WordsSerializerImpl::serialize(const Words& words) const
{
    nlohmann::json serialized;
    for(const auto& word : words)
    {
        serialized["words"].push_back(getJsonFromWord(word));
    }

//    serializedWord += specialCharacter + word.englishWord;
//    serializedWord += newLine + openBraces;
//    serializedWord += newLine + word.wordDescription.toString();
//    serializedWord += closeBraces + newLine;
//    return serializedWord;
    return serialized.dump();
}

Words WordsSerializerImpl::deserialize(const std::string&) const
{
    return Words();
}

namespace
{

nlohmann::json getJsonFromWord(const Word& word)
{
    nlohmann::json val = nlohmann::json::object();
    val["englishWord"] = word.englishWord;
    val["polishWord"] = word.polishWord;
    val["wordDescription"] = word.wordDescription.toString();
    return val;
}
}
