#include "DictionaryAvailabilityHandlerImpl.h"
#include "FileAccessMock.h"

#include "gtest/gtest.h"
#include "boost/assign.hpp"


using namespace ::testing;

namespace
{
const std::string dictionaryAvailabilityFilePath{"../database/dictionaryAvailability.txt"};
const std::string content{"car 1\n"
                          "air 0\n"};
const std::string emptyContent{};
DictionaryAvailability expectedDictionaryAvailability = boost::assign::map_list_of("car", WordAvailability{"car", true})
        ("air", WordAvailability{"air", false});
DictionaryAvailability emptyDictionaryAvailability{};
WordAvailability wordAvailability{"car", true};
}


class DictionaryAvailabilityHandlerImplTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    DictionaryAvailabilityHandlerImpl handler{fileAccess};
};

TEST_F(DictionaryAvailabilityHandlerImplTest, givenEmptyContent_shouldReturnEmptyDictionaryAvailability)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryAvailabilityFilePath)).WillOnce(Return(emptyContent));

    auto actualDictionaryAvailability = handler.read();

    EXPECT_EQ(actualDictionaryAvailability, emptyDictionaryAvailability);
}

TEST_F(DictionaryAvailabilityHandlerImplTest, givenAvailabilityContent_shouldReadDictionaryAvailability)
{
    EXPECT_CALL(*fileAccess, readContent(dictionaryAvailabilityFilePath)).WillOnce(Return(content));

    auto actualDictionaryAvailability = handler.read();

    EXPECT_EQ(actualDictionaryAvailability, expectedDictionaryAvailability);
}

TEST_F(DictionaryAvailabilityHandlerImplTest, givenWordAvailability_shouldAppendToFileWithDictionaryAvailability)
{
    EXPECT_CALL(*fileAccess, append(dictionaryAvailabilityFilePath, wordAvailability.toString() + "\n"));

    handler.add(wordAvailability);
}
