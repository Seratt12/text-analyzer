#include <gtest/gtest.h>
#include "core/textStatistics.h"

using namespace text_analyzer;

TEST(TextStatisticsSentences, EmptyString)
{
    EXPECT_EQ(getSentencesCount(""), 0u);
}

TEST(TextStatisticsSentences, NoSentence)
{
    EXPECT_EQ(getSentencesCount("hello world"), 0u);
}

TEST(TextStatisticsSentences, OneSentence)
{
    EXPECT_EQ(getSentencesCount("Hello."), 1u);
}

TEST(TextStatisticsSentences, Question)
{
    EXPECT_EQ(getSentencesCount("How are you?"), 1u);
}

TEST(TextStatisticsSentences, Exclamation)
{
    EXPECT_EQ(getSentencesCount("Hello!"), 1u);
}

TEST(TextStatisticsSentences, MultipleSentences)
{
    EXPECT_EQ(getSentencesCount("Hello. How are you? Fine!"), 3u);
}

TEST(TextStatisticsSentences, EllipsisCountsEach)
{
    // Документируем: "..." = 3
    EXPECT_EQ(getSentencesCount("Hello..."), 3u);
}

TEST(TextStatisticsSentences, CyrillicSentence)
{
    EXPECT_EQ(getSentencesCount("Привет. Как дела? Хорошо!"), 3u);
}

TEST(TextStatisticsSentences, OnlyPunctuation)
{
    EXPECT_EQ(getSentencesCount("...?!"), 5u);
}