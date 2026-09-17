#include "core/textStatistics.h"
#include <algorithm>
#include <numeric>
#include <cctype>
#include <unordered_map>
#include <cmath>
#include <boost/locale.hpp>

namespace
{
std::locale getLocale()
{
    static const std::locale loc = boost::locale::generator{ }("");
    return loc;
}

std::string toLowerCase(const std::string& sourceString)
{
    return boost::locale::to_lower(sourceString, getLocale());
}

bool isDelimiter(const char ch)
{
    if (std::isspace(static_cast<unsigned char>(ch)))
        return true;

    // Апостроф и дефис — НЕ разделители, даже если ispunct
    if (ch == '\'' || ch == '-')
        return false;


    return std::ispunct(static_cast<unsigned char>(ch)) != 0;
}
}

namespace text_analyzer
{
size_t getSymbolsCount(const std::string& source) noexcept
{
    size_t count = 0;
    for (unsigned char ch : source)
    {
        // Байты 0x80..0xBF — это "продолжения" символа,
        // они не начинают новый символ. Остальные — начинают.
        if ((ch & 0xC0) != 0x80)
            ++count;
    }
    return count;
}

size_t getWordsCount(const std::vector<std::string>& source)
{
    return source.size();
}

size_t getUniqueWordsCount(const std::vector<std::string>& source)
{
    return getUniqueWords(source).size();
}

size_t getSentencesCount(const std::string& source) noexcept
{
    size_t count = 0;
    for (char ch : source)
    {
        if (ch == '.' || ch == '?' || ch == '!')
            ++count;
    }
    return count;
}

double getAverageWordLength(const std::vector<std::string>& words)
{
    const size_t wordsCount = words.size();
    if (wordsCount == 0)
        return 0.0;

    const size_t totalChars = std::accumulate(words.begin(), words.end(), size_t{ 0 }, [ ](size_t sum, const std::string& word)
        {
            return sum + getSymbolsCount(word);
        });
    return static_cast<double>(totalChars) / wordsCount;
}

std::vector<std::pair<std::string, size_t>> getTopWords(const std::vector<std::string>& words, size_t count /* = 5 */)
{
    std::unordered_map<std::string, size_t> freq;

    for (const auto& word : words)
        ++freq[word];

    std::vector<std::pair<std::string, size_t>> sorted(freq.begin(), freq.end());

    std::sort(sorted.begin(), sorted.end(),
        [ ](const auto& a, const auto& b)
        {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    constexpr size_t topN = 5;
    if (sorted.size() > topN)
        sorted.resize(topN);

    return sorted;
}

AnalyzeTextResult getFullInfo(const std::string& source)
{
    AnalyzeTextResult result{ };
    result.chars = getSymbolsCount(source);
    result.sentences = getSentencesCount(source);

    const auto words = splitWords(source);
    result.words = getWordsCount(words);

    result.uniqueWords = getUniqueWordsCount(words);

    result.average_word_length = getAverageWordLength(words);
    result.topWords = getTopWords(words);

    return result;
}

std::vector<std::string> splitWords(const std::string& source)
{
    const std::string lowerString = toLowerCase(source);

    std::vector<std::string> result{ };
    std::string word;
    for (const auto ch : lowerString)
    {
        if (!isDelimiter(ch))
        {
            word += ch;
            continue;
        }

        if (!word.empty())
        {
            result.push_back(word);
            word.clear();
        }
    }
    if (!word.empty())
        result.push_back(word);

    return result;
}

std::unordered_set<std::string> getUniqueWords(const std::vector<std::string>& words)
{
    return { words.begin(), words.end() };
}
}