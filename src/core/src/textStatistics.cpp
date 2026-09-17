#include "core/textStatistics.h"
#include <algorithm>
#include <cctype>
#include <unordered_set>
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

size_t text_analyzer::TextStatistics::getSymbolsCount(const std::string& source) noexcept
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

size_t text_analyzer::TextStatistics::getWordsCount(const std::string& source)
{
    return splitWords(source).size();
}

size_t text_analyzer::TextStatistics::getUniqueWordsCount(const std::string& source)
{
    const auto allWords = splitWords(source);
    std::unordered_set<std::string> uniqueWords{ allWords.begin(), allWords.end() };
    return uniqueWords.size();
}

std::vector<std::string> text_analyzer::TextStatistics::splitWords(const std::string& source)
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