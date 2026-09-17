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

    static size_t getCountSymbols(const std::string& string) noexcept;
    static size_t getCountWords(const std::string& string);
private:
    static std::vector<std::string> splitWords(const std::string& string);
};
}