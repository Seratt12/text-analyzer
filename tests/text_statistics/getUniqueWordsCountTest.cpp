#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

TEST(TextStatisticsUnique, EmptyString)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("")), 0u);
}

TEST(TextStatisticsUnique, SingleWord)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("hello")), 1u);
}

TEST(TextStatisticsUnique, AllUnique)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("one two three")), 3u);
}

TEST(TextStatisticsUnique, AllSame)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("hello hello hello")), 1u);
}

TEST(TextStatisticsUnique, CaseInsensitive)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("Hello hello HELLO")), 1u);
}

TEST(TextStatisticsUnique, MixedCase)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("Hello world hello WORLD")), 2u);
}

TEST(TextStatisticsUnique, WithPunctuation)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("Hello, world! Hello.")), 2u);
}

TEST(TextStatisticsUnique, CyrillicUnique)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("Привет мир")), 2u);
}

TEST(TextStatisticsUnique, CyrillicSameWord)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("привет привет привет")), 1u);
}

TEST(TextStatisticsUnique, CyrillicDifferentCase)
{
    EXPECT_EQ(getUniqueWordsCount(splitWords("Привет привет")), 1u);
}

TEST(TextStatisticsUnique, LongText)
{
    const std::string text = "the quick brown fox jumps over the lazy dog";
    EXPECT_EQ(getUniqueWordsCount(splitWords(text)), 8u);
}