#include "core/textStatistics.h"
#include <algorithm>
#include <cctype>

namespace
{
std::string toLowerCase(const std::string& sourceString)
{
    std::string stringToLowerCase = sourceString;
    std::transform(stringToLowerCase.begin(), stringToLowerCase.end(), stringToLowerCase.begin(), [ ](char c)
        {
            return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        });
    return stringToLowerCase;
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

size_t text_analyzer::TextStatistics::getCountSymbols(const std::string& source) noexcept
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

size_t text_analyzer::TextStatistics::getCountWords(const std::string& source)
{
    return splitWords(source).size();
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