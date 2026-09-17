#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

// 
// getTopWords — базовые случаи
// 

TEST(TextStatisticsTopWords, EmptyString)
{
    const auto result = getTopWords(splitWords(""));
    EXPECT_TRUE(result.empty());
}

TEST(TextStatisticsTopWords, OnlySpaces)
{
    const auto result = getTopWords(splitWords("     "));
    EXPECT_TRUE(result.empty());
}

TEST(TextStatisticsTopWords, SingleWord)
{
    const auto result = getTopWords(splitWords("hello"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "hello");
    EXPECT_EQ(result[0].second, 1u);
}

TEST(TextStatisticsTopWords, TwoDifferentWords)
{
    const auto result = getTopWords(splitWords("hello world"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].first, "hello");
    EXPECT_EQ(result[0].second, 1u);
    EXPECT_EQ(result[1].first, "world");
    EXPECT_EQ(result[1].second, 1u);
}

// 
// getTopWords — частоты и сортировка
// 

TEST(TextStatisticsTopWords, SortedByFrequencyDescending)
{
    const auto result = getTopWords(splitWords("a a a b b c"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0].first, "a");
    EXPECT_EQ(result[0].second, 3u);
    EXPECT_EQ(result[1].first, "b");
    EXPECT_EQ(result[1].second, 2u);
    EXPECT_EQ(result[2].first, "c");
    EXPECT_EQ(result[2].second, 1u);
}

TEST(TextStatisticsTopWords, TieBreakedByAlphabet)
{
    const auto result = getTopWords(splitWords("b a b a c"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0].first, "a");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "b");
    EXPECT_EQ(result[1].second, 2u);
    EXPECT_EQ(result[2].first, "c");
    EXPECT_EQ(result[2].second, 1u);
}

TEST(TextStatisticsTopWords, TieBreakWithDifferentFrequencies)
{
    const auto result = getTopWords(splitWords("a a a c b"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0].first, "a");
    EXPECT_EQ(result[0].second, 3u);
    EXPECT_EQ(result[1].first, "b");
    EXPECT_EQ(result[1].second, 1u);
    EXPECT_EQ(result[2].first, "c");
    EXPECT_EQ(result[2].second, 1u);
}

// 
// getTopWords — ограничение до 5
// 

TEST(TextStatisticsTopWords, ExactlyFiveWords)
{
    const auto result = getTopWords(splitWords("a b c d e"));
    EXPECT_EQ(result.size(), 5u);
}

TEST(TextStatisticsTopWords, MoreThanFiveWords)
{
    const auto result = getTopWords(splitWords("a b c d e f g"));
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0].first, "a");
    EXPECT_EQ(result[1].first, "b");
    EXPECT_EQ(result[2].first, "c");
    EXPECT_EQ(result[3].first, "d");
    EXPECT_EQ(result[4].first, "e");
}

TEST(TextStatisticsTopWords, TopFiveByFrequencyNotAlphabet)
{
    const auto result = getTopWords(splitWords("z z z z z a b c d e f"));
    ASSERT_GE(result.size(), 1u);
    EXPECT_EQ(result[0].first, "z");
    EXPECT_EQ(result[0].second, 5u);
}

// 
// getTopWords — пунктуация и регистр
// 

TEST(TextStatisticsTopWords, CaseInsensitive)
{
    const auto result = getTopWords(splitWords("Hello hello HELLO"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "hello");
    EXPECT_EQ(result[0].second, 3u);
}

TEST(TextStatisticsTopWords, WithPunctuation)
{
    const auto result = getTopWords(splitWords("Hello, world! Hello."));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].first, "hello");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "world");
    EXPECT_EQ(result[1].second, 1u);
}

TEST(TextStatisticsTopWords, ApostropheAndHyphen)
{
    const auto result = getTopWords(splitWords("don't well-known don't"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].first, "don't");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "well-known");
    EXPECT_EQ(result[1].second, 1u);
}

// 
// getTopWords — кириллица
// 

TEST(TextStatisticsTopWords, CyrillicSimple)
{
    const auto result = getTopWords(splitWords("привет мир привет"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].first, "привет");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "мир");
    EXPECT_EQ(result[1].second, 1u);
}

TEST(TextStatisticsTopWords, CyrillicCaseInsensitive)
{
    const auto result = getTopWords(splitWords("Привет привет ПРИВЕТ"));
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].first, "привет");
    EXPECT_EQ(result[0].second, 3u);
}

TEST(TextStatisticsTopWords, CyrillicTieBreak)
{
    const auto result = getTopWords(splitWords("б а б а в"));
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0].first, "а");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "б");
    EXPECT_EQ(result[1].second, 2u);
    EXPECT_EQ(result[2].first, "в");
    EXPECT_EQ(result[2].second, 1u);
}

TEST(TextStatisticsTopWords, CyrillicTopFive)
{
    const auto result = getTopWords(splitWords(
        "мама мыла раму мама мыла окно мама мыла пол папа мыл машину"
    ));
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0].first, "мама");
    EXPECT_EQ(result[0].second, 3u);
    EXPECT_EQ(result[1].first, "мыла");
    EXPECT_EQ(result[1].second, 3u);
    // Дальше слова с частотой 1, порядок по алфавиту:
    EXPECT_EQ(result[2].first, "машину");
    EXPECT_EQ(result[3].first, "мыл");
    EXPECT_EQ(result[4].first, "окно");
}

// 
// getTopWords — смешанные алфавиты
// 

TEST(TextStatisticsTopWords, MixedAlphabets)
{
    const auto result = getTopWords(splitWords("Hello мир hello МИР"));
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].first, "hello");
    EXPECT_EQ(result[0].second, 2u);
    EXPECT_EQ(result[1].first, "мир");
    EXPECT_EQ(result[1].second, 2u);
}