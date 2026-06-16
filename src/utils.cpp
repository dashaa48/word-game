#include "utils.h"

#include <algorithm>
#include <cctype>

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool isValidWord(const std::string& str) {
    if (str.empty()) return false;
    for (unsigned char c : str) {
        if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

char getLastLetter(const std::string& word) {
    if (word.empty()) return '\0';
    return toLower(word).back();
}

char getSecondLastLetter(const std::string& word) {
    std::string lower = toLower(word);
    if (lower.size() < 2) return lower.empty() ? '\0' : lower[0];
    return lower[lower.size() - 2];
}

char getPreviousLetter(char c) {
    if (c <= 'a') return c;
    return c - 1;
}