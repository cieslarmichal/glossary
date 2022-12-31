#pragma once

#include <memory>

#include "../commands/AddWordToDictionaryCommand.h"
#include "../commands/CreateDictionaryCommand.h"
#include "../commands/CreateDictionaryFromCsvFileCommand.h"
#include "../commands/RemoveDictionaryCommand.h"
#include "../commands/RemoveWordFromDictionaryCommand.h"
#include "../commands/UpdateWordTranslationInDictionaryCommand.h"
#include "../DictionaryConfig.h"
#include "../queries/GetDictionariesEnglishWordsQuery.h"
#include "../queries/GetDictionariesNamesQuery.h"
#include "../queries/GetDictionariesQuery.h"
#include "../queries/GetDictionaryEnglishWordsQuery.h"
#include "../queries/GetDictionaryQuery.h"
#include "../queries/GetRandomWordFromDictionariesQuery.h"
#include "../queries/GetRandomWordFromDictionaryQuery.h"
#include "../queries/GetWordDescriptionQuery.h"
#include "fileSystem/FileAccess.h"
#include "httpClient/HttpClient.h"
#include "random/RandomNumberGenerator.h"

namespace glossary::dictionary
{
class DictionaryFactory
{
public:
    virtual ~DictionaryFactory() = default;

    virtual std::unique_ptr<AddWordToDictionaryCommand> createAddWordToDictionaryCommand() const = 0;
    virtual std::unique_ptr<CreateDictionaryCommand> createCreateDictionaryCommand() const = 0;
    virtual std::unique_ptr<CreateDictionaryFromCsvFileCommand> createCreateDictionaryFromCsvFileCommand() const = 0;
    virtual std::unique_ptr<RemoveDictionaryCommand> createRemoveDictionaryCommand() const = 0;
    virtual std::unique_ptr<RemoveWordFromDictionaryCommand> createRemoveWordFromDictionaryCommand() const = 0;
    virtual std::unique_ptr<UpdateWordTranslationInDictionaryCommand>
    createUpdateWordTranslationInDictionaryCommand() const = 0;
    virtual std::unique_ptr<GetDictionariesEnglishWordsQuery> createGetDictionariesEnglishWordsQuery() const = 0;
    virtual std::unique_ptr<GetDictionariesNamesQuery> createGetDictionariesNamesQuery() const = 0;
    virtual std::unique_ptr<GetDictionariesQuery> createGetDictionariesQuery() const = 0;
    virtual std::unique_ptr<GetDictionaryEnglishWordsQuery> createGetDictionaryEnglishWordsQuery() const = 0;
    virtual std::unique_ptr<GetDictionaryQuery> createGetDictionaryQuery() const = 0;
    virtual std::unique_ptr<GetRandomWordFromDictionariesQuery> createGetRandomWordFromDictionariesQuery() const = 0;
    virtual std::unique_ptr<GetRandomWordFromDictionaryQuery> createGetRandomWordFromDictionaryQuery() const = 0;
    virtual std::unique_ptr<GetWordDescriptionQuery> createGetWordDescriptionQuery() const = 0;

    static std::unique_ptr<DictionaryFactory>
    createDictionaryFactory(const std::shared_ptr<common::fileSystem::FileAccess>&,
                            const std::shared_ptr<common::httpClient::HttpClient>&,
                            const std::shared_ptr<common::random::RandomNumberGenerator>&, const DictionaryConfig&);
};
}
