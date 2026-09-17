#pragma once

#include <string>
#include <vector>
#include <unordered_set>

namespace text_analyzer
{
struct AnalyzeTextResult
{
    size_t chars;
    size_t words;
    size_t sentences;
    size_t uniqueWords;
    double average_word_length;
    std::vector<std::pair<std::string, size_t>> topWords;
};

size_t getSymbolsCount(const std::string& source) noexcept;
size_t getWordsCount(const std::vector<std::string>& source);
size_t getUniqueWordsCount(const std::vector<std::string>& source);
size_t getSentencesCount(const std::string& source) noexcept;
double getAverageWordLength(const std::vector<std::string>& words);
std::vector<std::pair<std::string, size_t>> getTopWords(const std::vector<std::string>& words, size_t count = 5);

std::vector<std::string> splitWords(const std::string& source);
std::unordered_set<std::string> getUniqueWords(const std::vector<std::string>& source);

AnalyzeTextResult getFullInfo(const std::string& source);
}