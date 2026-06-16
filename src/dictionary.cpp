#include "dictionary.h"

#include <fstream>
#include <random>

#include "utils.h"

Dictionary::Dictionary(const std::string& dictionaryPath) : path_(dictionaryPath) {
    for (char c = 'a'; c <= 'z'; ++c) {
        loadLetterFile(c);
    }
}

void Dictionary::loadLetterFile(char letter) {
    std::string filename = path_ + "/" + letter + ".txt";
    std::ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    std::string word;
    while (std::getline(file, word)) {
        if (word.empty()) continue;
        std::string lower = toLower(word);
        allWords_.insert(lower);
        int idx = letterToIndex(letter);
        if (idx >= 0) {
            wordsByLetter_[idx].push_back(lower);
        }
    }
}

bool Dictionary::contains(const std::string& word) const {
    return allWords_.find(toLower(word)) != allWords_.end();
}

std::string Dictionary::getRandomWord(char letter) const {
    int idx = letterToIndex(letter);
    if (idx < 0 || wordsByLetter_[idx].empty()) {
        return "";
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(wordsByLetter_[idx].size()) - 1);
    return wordsByLetter_[idx][dis(gen)];
}

std::string Dictionary::getRandomUnusedWord(
    char letter, const std::unordered_set<std::string>& usedWords) const {
    int idx = letterToIndex(letter);

    if (idx < 0 || wordsByLetter_[idx].empty()) {
        return "";
    }

    std::vector<std::string> available;

    for (const auto& word : wordsByLetter_[idx]) {
        if (usedWords.find(word) == usedWords.end()) {
            available.push_back(word);
        }
    }

    if (available.empty()) {
        return "";
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> dis(0, static_cast<int>(available.size()) - 1);

    return available[dis(gen)];
}
bool Dictionary::hasAvailableWords(char letter,
                                   const std::unordered_set<std::string>& usedWords) const {
    int idx = letterToIndex(letter);
    if (idx < 0) return false;

    for (const auto& word : wordsByLetter_[idx]) {
        if (usedWords.find(word) == usedWords.end()) {
            return true;
        }
    }
    return false;
}

int Dictionary::letterToIndex(char c) {
    char lower = std::tolower(static_cast<unsigned char>(c));
    if (lower >= 'a' && lower <= 'z') {
        return lower - 'a';
    }
    return -1;
}