#include <gtest/gtest.h>
#include "core/textStatistics.h"

using text_analyzer::TextStatistics;

TEST(TextStatisticsUnique, EmptyString)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount(""), 0u);
}

TEST(TextStatisticsUnique, SingleWord)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("hello"), 1u);
}

TEST(TextStatisticsUnique, AllUnique)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("one two three"), 3u);
}

TEST(TextStatisticsUnique, AllSame)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("hello hello hello"), 1u);
}

TEST(TextStatisticsUnique, CaseInsensitive)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("Hello hello HELLO"), 1u);
}

TEST(TextStatisticsUnique, MixedCase)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("Hello world hello WORLD"), 2u);
}

TEST(TextStatisticsUnique, WithPunctuation)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("Hello, world! Hello."), 2u);
}

TEST(TextStatisticsUnique, CyrillicUnique)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("Привет мир"), 2u);
}

TEST(TextStatisticsUnique, CyrillicSameWord)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("привет привет привет"), 1u);
}

TEST(TextStatisticsUnique, CyrillicDifferentCase)
{
    EXPECT_EQ(TextStatistics::getUniqueWordsCount("Привет привет"), 1u);
}

TEST(TextStatisticsUnique, LongText)
{
    const std::string text = "the quick brown fox jumps over the lazy dog";
    EXPECT_EQ(TextStatistics::getUniqueWordsCount(text), 8u);  // "the" повторяется
}