#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

TEST(TextStatisticsAvgWordLength, EmptyString)
{
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("")), 0.0);
}

TEST(TextStatisticsAvgWordLength, OnlySpaces)
{
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("     ")), 0.0);
}

TEST(TextStatisticsAvgWordLength, SingleWord)
{
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("hello")), 5.0);
}

TEST(TextStatisticsAvgWordLength, TwoWords)
{
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("hello world")), 5.0);
}

TEST(TextStatisticsAvgWordLength, DifferentLengths)
{
    // "a bb ccc" → (1+2+3)/3 = 2.0
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("a bb ccc")), 2.0);
}

TEST(TextStatisticsAvgWordLength, Cyrillic)
{
    // "Привет мир" → (6+3)/2 = 4.5
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("Привет мир")), 4.5);
}

TEST(TextStatisticsAvgWordLength, CyrillicWithPunctuation)
{
    // "Привет, мир!" → слова "привет"(6), "мир"(3) → 4.5
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("Привет, мир!")), 4.5);
}

TEST(TextStatisticsAvgWordLength, CyrillicLong)
{
    // "Мама мыла раму" → (4+4+4)/3 = 4.0
    EXPECT_DOUBLE_EQ(getAverageWordLength(splitWords("Мама мыла раму")), 4.0);
}