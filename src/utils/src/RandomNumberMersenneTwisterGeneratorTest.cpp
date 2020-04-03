#include "RandomNumberMersenneTwisterGenerator.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
constexpr int rangeStart{2};
constexpr int rangeEnd{10};
}

class RandomNumberMersenneTwisterGeneratorTest : public Test
{
public:
    RandomNumberMersenneTwisterGenerator randomGenerator;
};

TEST_F(RandomNumberMersenneTwisterGeneratorTest, givenInvalidRangeArguments_shouldThrowInvalidArgument)
{
    ASSERT_THROW(randomGenerator.generate(rangeEnd, rangeStart), std::invalid_argument);
}

TEST_F(RandomNumberMersenneTwisterGeneratorTest,
       givenValidRangeArguments_shouldGenerateNumberThatIsInGivenRange)
{
    const auto randomNumber = randomGenerator.generate(rangeStart, rangeEnd);

    ASSERT_TRUE(randomNumber >= rangeStart);
    ASSERT_TRUE(randomNumber <= rangeEnd);
}