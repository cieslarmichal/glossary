#pragma once

#include <memory>

#include "DictionaryNameSelector.h"
#include "DictionaryNamesRetriever.h"
#include "WordsDictionaryMembershipFinder.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionary
{
class DefaultDictionaryNamesRetriever : public DictionaryNamesRetriever
{
public:
    explicit DefaultDictionaryNamesRetriever(std::shared_ptr<repository::DictionaryRepository>);

    std::vector<std::string> retrieveDictionaryNames() const override;
    std::vector<std::string>
    retrieveDictionaryNamesContainingEnglishWord(const std::string& englishWord) const override;
    std::vector<std::string> retrieveDictionaryNamesContainingEnglishWordTranslation(
        const std::string& englishWordTranslation) const override;

private:
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    DictionaryNameSelector dictionaryNameSelector;
    WordsDictionaryMembershipFinder wordsDictionaryMembershipFinder;
};
}