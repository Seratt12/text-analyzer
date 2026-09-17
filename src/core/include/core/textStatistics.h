#pragma once

#include <string>
#include <vector>

namespace text_analyzer
{
class TextStatistics
{
public:
    TextStatistics() = default;
    ~TextStatistics() = default;

    static size_t getSymbolsCount(const std::string& string) noexcept;
    static size_t getWordsCount(const std::string& string);
    static size_t getUniqueWordsCount(const std::string& string);
private:
    static std::vector<std::string> splitWords(const std::string& string);
};
}