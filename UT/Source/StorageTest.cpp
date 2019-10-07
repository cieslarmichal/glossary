#include "Storage.h"

#include "gtest/gtest.h"

using namespace ::testing;

class StorageTest : public Test
{
public:
    Storage<std::string, std::string> emptyStorage{{}};
    Storage<std::string, std::string> nonEmptyStorage{{{"key", "object"}}};
};

TEST_F(StorageTest, givenEmptyStorage_getShouldReturnNone)
{
    auto result = emptyStorage.get("notExistingName");

    ASSERT_EQ(result, boost::none);
}

TEST_F(StorageTest, givenNonEmptyStorage_shouldReturnObject)
{
    auto result = nonEmptyStorage.get("key");

    ASSERT_EQ(result, std::string{"object"});
}

