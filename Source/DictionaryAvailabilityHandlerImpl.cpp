#include "DictionaryAvailabilityHandlerImpl.h"


#include "StringHelper.h"
#include <sstream>

const std::string dictionaryAvailabilityFilePath{"../database/dictionaryAvailability.txt"};

DictionaryAvailabilityHandlerImpl::DictionaryAvailabilityHandlerImpl(FileAccess& access) : fileAccess{access}
{
}

std::map<EnglishWord, WordAvailability> DictionaryAvailabilityHandlerImpl::read() const
{
    auto dictionaryAvailabilityContent = fileAccess.readContent(dictionaryAvailabilityFilePath);
    return processDictionaryAvailabilityContent(dictionaryAvailabilityContent);
}

std::map<EnglishWord, WordAvailability>
DictionaryAvailabilityHandlerImpl::processDictionaryAvailabilityContent(const std::string& availabilityContent) const
{
    std::map<EnglishWord, WordAvailability> wordsAvailability;

    for (const auto& line : stringHelper::getSplitLines(availabilityContent))
    {
        if(not line.empty())
        {
            auto wordAvailability = getWordAvailability(line);
            wordsAvailability[wordAvailability.name] = wordAvailability;
        }
    }

    return wordsAvailability;
}

WordAvailability DictionaryAvailabilityHandlerImpl::getWordAvailability(const std::string& line) const
{
    std::stringstream lineStream{line};
    bool descriptionExists = false;
    EnglishWord word;
    lineStream >> word >> descriptionExists;
    return WordAvailability({word, descriptionExists});

}

void DictionaryAvailabilityHandlerImpl::add(const WordAvailability& wordAvailability) const
{
    fileAccess.append(dictionaryAvailabilityFilePath, wordAvailability.toString() + "\n");
}
