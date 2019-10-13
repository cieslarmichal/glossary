#include "DictionaryAvailabilityHandlerImpl.h"


#include "StringHelper.h"
#include <sstream>
#include <iostream>
#include "Exceptions/FileNotFound.h"


const std::string DictionaryAvailabilityHandlerImpl::dictionaryAvailabilityFilePath{
        "../database/dictionaryAvailability.txt"};

DictionaryAvailabilityHandlerImpl::DictionaryAvailabilityHandlerImpl(std::shared_ptr<const FileAccess> access)
        : fileAccess{access}
{
}

std::map<EnglishWord, WordAvailability> DictionaryAvailabilityHandlerImpl::read() const
{
    std::string dictionaryAvailabilityContent;
    try
    {
        dictionaryAvailabilityContent = fileAccess->readContent(dictionaryAvailabilityFilePath);

    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return {};
    }

    return processDictionaryAvailabilityContent(dictionaryAvailabilityContent);
}

std::map<EnglishWord, WordAvailability>
DictionaryAvailabilityHandlerImpl::processDictionaryAvailabilityContent(const std::string& availabilityContent) const
{
    std::map<EnglishWord, WordAvailability> wordsAvailability;

    for (const auto& line : stringHelper::getSplitLines(availabilityContent))
    {
        if (not line.empty())
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
    try
    {
        fileAccess->append(dictionaryAvailabilityFilePath, wordAvailability.toString() + "\n");
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
    }
}
