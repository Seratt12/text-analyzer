#include <gtest/gtest.h>
#include "core/textStatistics.h"

using text_analyzer::TextStatistics;

//
// getSymbolsCount
//

TEST(TextStatisticsSymbols, EmptyString)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount(""), 0u);
}

TEST(TextStatisticsSymbols, SingleChar)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("a"), 1u);
}

TEST(TextStatisticsSymbols, SimpleAscii)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("hello"), 5u);
}

TEST(TextStatisticsSymbols, WithSpaces)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("hello world"), 11u);
}

TEST(TextStatisticsSymbols, WithPunctuation)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("Hello, world!"), 13u);
}

TEST(TextStatisticsSymbols, OnlySpaces)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("     "), 5u);
}

TEST(TextStatisticsSymbols, CyrillicCountsBytes)
{
    EXPECT_EQ(TextStatistics::getSymbolsCount("Привет"), 6u);
}