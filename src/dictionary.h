/**
 * @file dictionary.h
 * @brief Dictionary class for word storage
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>
#include <vector>

/**
 * @class Dictionary
 * @brief Loads and stores words from text files
 */
class Dictionary {
   public:
    /**
     * @brief Constructor
     * @param dictionaryPath Path to dictionary folder
     */
    explicit Dictionary(const std::string& dictionaryPath);

    /**
     * @brief Checks if word exists in dictionary (case-insensitive)
     * @param word Word to check (any case, e.g. "Apple" or "APPLE")
     * @return true if word exists in dictionary files
     */
    bool contains(const std::string& word) const;

    /**
     * @brief Gets random word starting with given letter
     * @param letter Starting letter
     * @return Word or empty string if none
     */
    std::string getRandomWord(char letter) const;

    /**
     * @brief Gets random unused word starting with given letter
     * @param letter Starting letter
     * @param usedWords Already used words
     * @return Unused word or empty string if none
     */
    std::string getRandomUnusedWord(char letter,
                                    const std::unordered_set<std::string>& usedWords) const;

    /**
     * @brief Checks if there are unused words for a letter
     * @param letter Letter to check
     * @param usedWords Set of already used words
     * @return true if available words exist
     */
    bool hasAvailableWords(char letter, const std::unordered_set<std::string>& usedWords) const;

   private:
    static constexpr int ALPHABET_SIZE = 26;

    std::string path_;
    std::unordered_set<std::string> allWords_;
    std::vector<std::string> wordsByLetter_[ALPHABET_SIZE];  // a-z

    static int letterToIndex(char c);
    void loadLetterFile(char letter);
};

#endif  // DICTIONARY_H