#pragma once

#include <memory>

#include "DictionaryNameSelector.h"
#include "DictionaryNamesRetriever.h"
#include "WordsDictionaryMembershipFinder.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryNamesRetriever : public DictionaryNamesRetriever
{
public:
    explicit DefaultDictionaryNamesRetriever(std::shared_ptr<repository::DictionaryRepository>);

    DictionaryNames retrieveDictionaryNames() const override;
    DictionaryNames
    retrieveDictionaryNamesContainingEnglishWord(const std::string& englishWord) const override;
    DictionaryNames retrieveDictionaryNamesContainingEnglishWordTranslation(
        const std::string& englishWordTranslation) const override;

private:
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    DictionaryNameSelector dictionaryNameSelector;
    WordsDictionaryMembershipFinder wordsDictionaryMembershipFinder;
};
}