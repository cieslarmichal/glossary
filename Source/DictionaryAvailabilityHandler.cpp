#include "DictionaryAvailabilityHandler.h"


#include "StringHelper.h"
#include <sstream>

const std::string wordExistenceInformationsFilePath{"../database/list.txt"};

DictionaryAvailabilityHandler::DictionaryAvailabilityHandler(FileAccess & access) : fileAccess{access}
{
}

std::map<EnglishWord, WordAvailability> DictionaryAvailabilityHandler::read() const
{
    auto dictionaryAvailabilityContent = fileAccess.readContent(wordExistenceInformationsFilePath);
    return processDictionaryAvailabilityContent(dictionaryAvailabilityContent);
}

std::map<EnglishWord, WordAvailability>
DictionaryAvailabilityHandler::processDictionaryAvailabilityContent(const std::string & availabilityContent) const
{
    std::map<EnglishWord, WordAvailability> wordsAvailability;

    for (const auto &line : stringHelper::getSplitLines(availabilityContent))
    {
        auto wordAvailability = getWordAvailability(line);
        wordsAvailability[wordAvailability.name] = wordAvailability;
    }

    return wordsAvailability;
}

WordAvailability DictionaryAvailabilityHandler::getWordAvailability(const std::string & line) const
{
    std::stringstream lineStream{line};
    bool descriptionExists = false;
    EnglishWord word;
    lineStream >> word >> descriptionExists;
    return WordAvailability({word, descriptionExists});

}

void DictionaryAvailabilityHandler::add(const WordAvailability & wordAvailability) const
{
    fileAccess.append(wordExistenceInformationsFilePath, wordAvailability.toString());
}
