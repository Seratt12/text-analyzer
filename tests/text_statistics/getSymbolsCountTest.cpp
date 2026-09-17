#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

TEST(TextStatisticsSymbols, EmptyString)
{
    EXPECT_EQ(getSymbolsCount(""), 0u);
}

TEST(TextStatisticsSymbols, SingleChar)
{
    EXPECT_EQ(getSymbolsCount("a"), 1u);
}

TEST(TextStatisticsSymbols, SimpleAscii)
{
    EXPECT_EQ(getSymbolsCount("hello"), 5u);
}

TEST(TextStatisticsSymbols, WithSpaces)
{
    EXPECT_EQ(getSymbolsCount("hello world"), 11u);
}

TEST(TextStatisticsSymbols, WithPunctuation)
{
    EXPECT_EQ(getSymbolsCount("Hello, world!"), 13u);
}

TEST(TextStatisticsSymbols, OnlySpaces)
{
    EXPECT_EQ(getSymbolsCount("     "), 5u);
}

TEST(TextStatisticsSymbols, CyrillicCountsBytes)
{
    EXPECT_EQ(getSymbolsCount("Привет"), 6u);
}