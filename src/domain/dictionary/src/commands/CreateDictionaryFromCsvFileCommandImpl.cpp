#include "CreateDictionaryFromCsvFileCommandImpl.h"

namespace glossary::dictionary
{
CreateDictionaryFromCsvFileCommandImpl::CreateDictionaryFromCsvFileCommandImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::unique_ptr<DictionaryWordsCsvReader> dictionaryWordsCsvReaderInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      dictionaryWordsCsvReader{std::move(dictionaryWordsCsvReaderInit)}
{
}

void CreateDictionaryFromCsvFileCommandImpl::createDictionaryFromCsvFile(const std::string& dictionaryName,
                                                                         const std::string& dictionaryWordsCsvFilePath)
{
    const auto dictionaryWordsFromFile = dictionaryWordsCsvReader->readDictionaryWords(dictionaryWordsCsvFilePath);

    dictionaryRepository->addDictionary({dictionaryName, dictionaryWordsFromFile});
}

}
