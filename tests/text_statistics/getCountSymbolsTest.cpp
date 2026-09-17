#include <gtest/gtest.h>
#include "core/textStatistics.h"

using text_analyzer::TextStatistics;

//
// getCountSymbols
//

TEST(TextStatisticsSymbols, EmptyString)
{
    EXPECT_EQ(TextStatistics::getCountSymbols(""), 0u);
}

TEST(TextStatisticsSymbols, SingleChar)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("a"), 1u);
}

TEST(TextStatisticsSymbols, SimpleAscii)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("hello"), 5u);
}

TEST(TextStatisticsSymbols, WithSpaces)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("hello world"), 11u);
}

TEST(TextStatisticsSymbols, WithPunctuation)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("Hello, world!"), 13u);
}

TEST(TextStatisticsSymbols, OnlySpaces)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("     "), 5u);
}

TEST(TextStatisticsSymbols, CyrillicCountsBytes)
{
    EXPECT_EQ(TextStatistics::getCountSymbols("Привет"), 6u);
}