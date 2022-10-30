#include "CreateDictionaryFromCsvFileCommandImpl.h"

#include "gtest/gtest.h"

#include "../readers/DictionaryWordsCsvReaderMock.h"
#include "../repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string absoluteDictionaryWordsPath{"absolutePathToDictionaryWords.csv"};
const std::string dictionaryName{"dictionaryName1"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const Dictionary dictionary{dictionaryName, dictionaryWords};
}

class CreateDictionaryFromCsvFileCommandImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    std::unique_ptr<DictionaryWordsCsvReaderMock> readerInit =
        std::make_unique<StrictMock<DictionaryWordsCsvReaderMock>>();
    DictionaryWordsCsvReaderMock* reader = readerInit.get();

    CreateDictionaryFromCsvFileCommandImpl command{dictionaryRepository, std::move(readerInit)};
};

TEST_F(CreateDictionaryFromCsvFileCommandImplTest, shouldCreateDictionaryFromCsvFile)
{
    EXPECT_CALL(*reader, readDictionaryWords(absoluteDictionaryWordsPath)).WillOnce(Return(dictionaryWords));

    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionary));

    command.createDictionaryFromCsvFile(dictionaryName, absoluteDictionaryWordsPath);
}
