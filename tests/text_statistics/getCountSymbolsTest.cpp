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
    // ВНИМАНИЕ: getCountSymbols считает БАЙТЫ, не символы.
    // "Привет" в UTF-8 — 12 байт (6 букв × 2 байта).
    // Этот тест документирует текущее поведение.
    EXPECT_EQ(TextStatistics::getCountSymbols("Привет"), 12u);
}