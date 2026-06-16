/**
 * @file utils.h
 * @brief Utility functions for string operations
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Converts string to lowercase
 * @param str Input string
 * @return Lowercase string
 */
std::string toLower(const std::string& str);

/**
 * @brief Checks if string contains only letters
 * @param str Input string
 * @return true if valid word
 */
bool isValidWord(const std::string& str);

/**
 * @brief Gets last significant letter of a word
 * @param word Input word
 * @return Last letter character
 */
char getLastLetter(const std::string& word);

/**
 * @brief Gets second last significant letter of a word
 * @param word Input word
 * @return Second last letter character, or '\0' if not enough letters
 */
char getSecondLastLetter(const std::string& word);

/**
 * @brief Gets previous letter in alphabet
 * @param c Current letter
 * @return Previous letter, or same if 'a'
 */
char getPreviousLetter(char c);

#endif  // UTILS_H