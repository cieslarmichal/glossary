#include "WordSerializerImpl.h"

namespace
{
const auto specialCharacter = "~";
const std::string newLine = "\n";
const auto openBraces = "{";
const auto closeBraces = "}";
}

std::string WordSerializerImpl::serialize(const Word& word) const
{
    std::string serializedWord;
    serializedWord += specialCharacter + word.englishWord;
    serializedWord += newLine + openBraces;
    serializedWord += newLine + word.wordDescription.toString();
    serializedWord += closeBraces + newLine;
    return serializedWord;
}
