#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

//
// getWordsCount — базовые случаи
//

TEST(TextStatisticsWords, EmptyString)
{
    EXPECT_EQ(getWordsCount(splitWords("")), 0u);
}

TEST(TextStatisticsWords, SingleWord)
{
    EXPECT_EQ(getWordsCount(splitWords("hello")), 1u);
}

TEST(TextStatisticsWords, TwoWords)
{
    EXPECT_EQ(getWordsCount(splitWords("hello world")), 2u);
}

TEST(TextStatisticsWords, ThreeWords)
{
    EXPECT_EQ(getWordsCount(splitWords("one two three")), 3u);
}

TEST(TextStatisticsWords, OnlySpaces)
{
    EXPECT_EQ(getWordsCount(splitWords("     ")), 0u);
}

TEST(TextStatisticsWords, MultipleSpacesBetweenWords)
{
    EXPECT_EQ(getWordsCount(splitWords("hello     world")), 2u);
}

TEST(TextStatisticsWords, LeadingSpaces)
{
    EXPECT_EQ(getWordsCount(splitWords("   hello")), 1u);
}

TEST(TextStatisticsWords, TrailingSpaces)
{
    EXPECT_EQ(getWordsCount(splitWords("hello   ")), 1u);
}

TEST(TextStatisticsWords, LeadingAndTrailingSpaces)
{
    EXPECT_EQ(getWordsCount(splitWords("   hello world   ")), 2u);
}

TEST(TextStatisticsWords, TabsAndNewlines)
{
    EXPECT_EQ(getWordsCount(splitWords("hello\tworld\ntest")), 3u);
}

// 
// getWordsCount — пунктуация
//

TEST(TextStatisticsWords, SimplePunctuation)
{
    EXPECT_EQ(getWordsCount(splitWords("Hello, world!")), 2u);
}

TEST(TextStatisticsWords, MultiplePunctuation)
{
    EXPECT_EQ(getWordsCount(splitWords("Hello... world?!")), 2u);
}

TEST(TextStatisticsWords, OnlyPunctuation)
{
    EXPECT_EQ(getWordsCount(splitWords(".,!?;:")), 0u);
}

TEST(TextStatisticsWords, PunctuationAroundWords)
{
    EXPECT_EQ(getWordsCount(splitWords("(hello) [world] {test}")), 3u);
}

TEST(TextStatisticsWords, Quotes)
{
    EXPECT_EQ(getWordsCount(splitWords("\"hello\" 'world'")), 2u);
}

// 
// getWordsCount — апостроф и дефис
//

TEST(TextStatisticsWords, Apostrophe)
{
    EXPECT_EQ(getWordsCount(splitWords("don't")), 1u);
}

TEST(TextStatisticsWords, Hyphen)
{
    EXPECT_EQ(getWordsCount(splitWords("well-known")), 1u);
}

TEST(TextStatisticsWords, ApostropheInSentence)
{
    EXPECT_EQ(getWordsCount(splitWords("It's a test")), 3u);
}

TEST(TextStatisticsWords, HyphenInSentence)
{
    EXPECT_EQ(getWordsCount(splitWords("It's a well-known fact.")), 4u);
}

TEST(TextStatisticsWords, MultipleHyphens)
{
    EXPECT_EQ(getWordsCount(splitWords("state-of-the-art solution")), 2u);
}

// ============================================================
// getWordsCount — регистр
// ============================================================

TEST(TextStatisticsWords, MixedCase)
{
    EXPECT_EQ(getWordsCount(splitWords("Hello HELLO hello")), 3u);
}

TEST(TextStatisticsWords, AllUppercase)
{
    EXPECT_EQ(getWordsCount(splitWords("HELLO WORLD")), 2u);
}

// 
// getWordsCount — кириллица
// 

TEST(TextStatisticsWords, CyrillicSimple)
{
    EXPECT_EQ(getWordsCount(splitWords("Привет мир")), 2u);
}

TEST(TextStatisticsWords, CyrillicWithPunctuation)
{
    EXPECT_EQ(getWordsCount(splitWords("Привет, мир!")), 2u);
}

TEST(TextStatisticsWords, CyrillicWithHyphen)
{
    EXPECT_EQ(getWordsCount(splitWords("кто-то")), 1u);
}

TEST(TextStatisticsWords, CyrillicMixedWithAscii)
{
    EXPECT_EQ(getWordsCount(splitWords("Hello, мир!")), 2u);
}

TEST(TextStatisticsWords, CyrillicMultipleSpaces)
{
    EXPECT_EQ(getWordsCount(splitWords("Привет    мир")), 2u);
}

TEST(TextStatisticsWords, CyrillicSentence)
{
    EXPECT_EQ(getWordsCount(splitWords("Привет, как дела? Хорошо!")), 4u);
}

// 
// getWordsCount — составные случаи
// 

TEST(TextStatisticsWords, LongSentence)
{
    const std::string text =
        "The quick brown fox jumps over the lazy dog.";
    EXPECT_EQ(getWordsCount(splitWords(text)), 9u);
}

TEST(TextStatisticsWords, SentenceWithApostrophesAndHyphens)
{
    const std::string text =
        "It's a well-known fact that don't-contractions are tricky.";
    EXPECT_EQ(getWordsCount(splitWords(text)), 8u);
}

TEST(TextStatisticsWords, OnlyOneDelimiter)
{
    EXPECT_EQ(getWordsCount(splitWords(",")), 0u);
}

TEST(TextStatisticsWords, NewlinesAndTabs)
{
    EXPECT_EQ(getWordsCount(splitWords("one\ntwo\tthree\r\nfour")), 4u);
}