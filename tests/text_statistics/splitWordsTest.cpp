#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

// 
// splitWords — базовые случаи
// 

TEST(SplitWords, EmptyString)
{
    EXPECT_TRUE(splitWords("").empty());
}

TEST(SplitWords, OnlySpaces)
{
    EXPECT_TRUE(splitWords("     ").empty());
}

TEST(SplitWords, SingleWord)
{
    const auto words = splitWords("hello");
    ASSERT_EQ(words.size(), 1u);
    EXPECT_EQ(words[0], "hello");
}

TEST(SplitWords, TwoWords)
{
    const auto words = splitWords("hello world");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "world");
}

TEST(SplitWords, MultipleSpaces)
{
    const auto words = splitWords("  hello   world  ");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "world");
}

TEST(SplitWords, TabsAndNewlines)
{
    const auto words = splitWords("one\ttwo\nthree\r\nfour");
    ASSERT_EQ(words.size(), 4u);
    EXPECT_EQ(words[0], "one");
    EXPECT_EQ(words[3], "four");
}

// 
// splitWords — пунктуация
// 

TEST(SplitWords, Punctuation)
{
    const auto words = splitWords("Hello, world!");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "world");
}

TEST(SplitWords, OnlyPunctuation)
{
    EXPECT_TRUE(splitWords(".,!?;:").empty());
}

TEST(SplitWords, PunctuationAroundWords)
{
    const auto words = splitWords("(hello) [world] {test}");
    ASSERT_EQ(words.size(), 3u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[2], "test");
}

// 
// splitWords — апостроф и дефис
// 

TEST(SplitWords, Apostrophe)
{
    const auto words = splitWords("don't");
    ASSERT_EQ(words.size(), 1u);
    EXPECT_EQ(words[0], "don't");
}

TEST(SplitWords, Hyphen)
{
    const auto words = splitWords("well-known");
    ASSERT_EQ(words.size(), 1u);
    EXPECT_EQ(words[0], "well-known");
}

TEST(SplitWords, ApostropheAndHyphen)
{
    const auto words = splitWords("It's a well-known fact.");
    ASSERT_EQ(words.size(), 4u);
    EXPECT_EQ(words[0], "it's");
    EXPECT_EQ(words[2], "well-known");
}

// ============================================================
// splitWords — регистр
// ============================================================

TEST(SplitWords, Lowercases)
{
    const auto words = splitWords("Hello HELLO hello");
    ASSERT_EQ(words.size(), 3u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "hello");
    EXPECT_EQ(words[2], "hello");
}

TEST(SplitWords, MixedCase)
{
    const auto words = splitWords("HeLLo WoRLd");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "world");
}

// 
// splitWords — кириллица
//

TEST(SplitWords, Cyrillic)
{
    const auto words = splitWords("Привет мир");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "привет");
    EXPECT_EQ(words[1], "мир");
}

TEST(SplitWords, CyrillicWithPunctuation)
{
    const auto words = splitWords("Привет, мир!");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "привет");
    EXPECT_EQ(words[1], "мир");
}

TEST(SplitWords, CyrillicWithHyphen)
{
    const auto words = splitWords("кто-то");
    ASSERT_EQ(words.size(), 1u);
    EXPECT_EQ(words[0], "кто-то");
}

TEST(SplitWords, CyrillicLowercase)
{
    const auto words = splitWords("Привет ПРИВЕТ ПрИвЕт");
    ASSERT_EQ(words.size(), 3u);
    EXPECT_EQ(words[0], "привет");
    EXPECT_EQ(words[1], "привет");
    EXPECT_EQ(words[2], "привет");
}

TEST(SplitWords, MixedAlphabets)
{
    const auto words = splitWords("Hello, мир!");
    ASSERT_EQ(words.size(), 2u);
    EXPECT_EQ(words[0], "hello");
    EXPECT_EQ(words[1], "мир");
}