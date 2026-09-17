#include <gtest/gtest.h>
#include "core/textStatistics.h"

using text_analyzer::TextStatistics;

//
// getCountWords — базовые случаи
//

TEST(TextStatisticsWords, EmptyString)
{
    EXPECT_EQ(TextStatistics::getCountWords(""), 0u);
}

TEST(TextStatisticsWords, SingleWord)
{
    EXPECT_EQ(TextStatistics::getCountWords("hello"), 1u);
}

TEST(TextStatisticsWords, TwoWords)
{
    EXPECT_EQ(TextStatistics::getCountWords("hello world"), 2u);
}

TEST(TextStatisticsWords, ThreeWords)
{
    EXPECT_EQ(TextStatistics::getCountWords("one two three"), 3u);
}

TEST(TextStatisticsWords, OnlySpaces)
{
    EXPECT_EQ(TextStatistics::getCountWords("     "), 0u);
}

TEST(TextStatisticsWords, MultipleSpacesBetweenWords)
{
    EXPECT_EQ(TextStatistics::getCountWords("hello     world"), 2u);
}

TEST(TextStatisticsWords, LeadingSpaces)
{
    EXPECT_EQ(TextStatistics::getCountWords("   hello"), 1u);
}

TEST(TextStatisticsWords, TrailingSpaces)
{
    EXPECT_EQ(TextStatistics::getCountWords("hello   "), 1u);
}

TEST(TextStatisticsWords, LeadingAndTrailingSpaces)
{
    EXPECT_EQ(TextStatistics::getCountWords("   hello world   "), 2u);
}

TEST(TextStatisticsWords, TabsAndNewlines)
{
    EXPECT_EQ(TextStatistics::getCountWords("hello\tworld\ntest"), 3u);
}

//
// getCountWords — пунктуация
//

TEST(TextStatisticsWords, SimplePunctuation)
{
    EXPECT_EQ(TextStatistics::getCountWords("Hello, world!"), 2u);
}

TEST(TextStatisticsWords, MultiplePunctuation)
{
    EXPECT_EQ(TextStatistics::getCountWords("Hello... world?!"), 2u);
}

TEST(TextStatisticsWords, OnlyPunctuation)
{
    EXPECT_EQ(TextStatistics::getCountWords(".,!?;:"), 0u);
}

TEST(TextStatisticsWords, PunctuationAroundWords)
{
    EXPECT_EQ(TextStatistics::getCountWords("(hello) [world] {test}"), 3u);
}

TEST(TextStatisticsWords, Quotes)
{
    EXPECT_EQ(TextStatistics::getCountWords("\"hello\" 'world'"), 2u);
}

//
// getCountWords — апостроф и дефис
//

TEST(TextStatisticsWords, Apostrophe)
{
    EXPECT_EQ(TextStatistics::getCountWords("don't"), 1u);
}

TEST(TextStatisticsWords, Hyphen)
{
    EXPECT_EQ(TextStatistics::getCountWords("well-known"), 1u);
}

TEST(TextStatisticsWords, ApostropheInSentence)
{
    EXPECT_EQ(TextStatistics::getCountWords("It's a test"), 3u);
}

TEST(TextStatisticsWords, HyphenInSentence)
{
    EXPECT_EQ(TextStatistics::getCountWords("It's a well-known fact."), 4u);
}

TEST(TextStatisticsWords, MultipleHyphens)
{
    EXPECT_EQ(TextStatistics::getCountWords("state-of-the-art solution"), 2u);
}

// 
// getCountWords — регистр
// 

TEST(TextStatisticsWords, MixedCase)
{
    EXPECT_EQ(TextStatistics::getCountWords("Hello HELLO hello"), 3u);
}

TEST(TextStatisticsWords, AllUppercase)
{
    EXPECT_EQ(TextStatistics::getCountWords("HELLO WORLD"), 2u);
}

// 
// getCountWords — кириллица
// 

TEST(TextStatisticsWords, CyrillicSimple)
{
    EXPECT_EQ(TextStatistics::getCountWords("Привет мир"), 2u);
}

TEST(TextStatisticsWords, CyrillicWithPunctuation)
{
    EXPECT_EQ(TextStatistics::getCountWords("Привет, мир!"), 2u);
}

TEST(TextStatisticsWords, CyrillicWithHyphen)
{
    EXPECT_EQ(TextStatistics::getCountWords("кто-то"), 1u);
}

TEST(TextStatisticsWords, CyrillicMixedWithAscii)
{
    EXPECT_EQ(TextStatistics::getCountWords("Hello, мир!"), 2u);
}

TEST(TextStatisticsWords, CyrillicMultipleSpaces)
{
    EXPECT_EQ(TextStatistics::getCountWords("Привет    мир"), 2u);
}

TEST(TextStatisticsWords, CyrillicSentence)
{
    EXPECT_EQ(TextStatistics::getCountWords("Привет, как дела? Хорошо!"), 4u);
}

// 
// getCountWords — составные случаи
// 

TEST(TextStatisticsWords, LongSentence)
{
    const std::string text =
        "The quick brown fox jumps over the lazy dog.";
    EXPECT_EQ(TextStatistics::getCountWords(text), 9u);
}

TEST(TextStatisticsWords, SentenceWithApostrophesAndHyphens)
{
    const std::string text =
        "It's a well-known fact that don't-contractions are tricky.";
    EXPECT_EQ(TextStatistics::getCountWords(text), 8u);
}

TEST(TextStatisticsWords, OnlyOneDelimiter)
{
    EXPECT_EQ(TextStatistics::getCountWords(","), 0u);
}

TEST(TextStatisticsWords, NewlinesAndTabs)
{
    EXPECT_EQ(TextStatistics::getCountWords("one\ntwo\tthree\r\nfour"), 4u);
}