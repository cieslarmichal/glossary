#include "UpdateWordTranslationInDictionaryCommandImpl.h"

namespace glossary::dictionary
{
UpdateWordTranslationInDictionaryCommandImpl::UpdateWordTranslationInDictionaryCommandImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}
void UpdateWordTranslationInDictionaryCommandImpl::updateWordTranslation(const std::string& dictionaryName,
                                                                         const std::string& englishWord,
                                                                         const std::string& translation)
{
    dictionaryRepository->changeWordTranslationFromDictionary(englishWord, translation, dictionaryName);
}

}
