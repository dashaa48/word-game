#include "player.h"

#include <iostream>

#include "utils.h"

HumanPlayer::HumanPlayer(std::string name) : name_(std::move(name)) {}

std::string HumanPlayer::makeMove(char requiredLetter, const Dictionary& dictionary,
                                  const std::unordered_set<std::string>& usedWords) {
    std::cout << name_ << ", enter word on letter '" << requiredLetter << "': ";
    std::string word;
    std::getline(std::cin, word);

    std::string lower = toLower(word);
    if (lower.empty()) {
        std::cout << "Empty input - you surrender!" << std::endl;
        return "";
    }

    if (!isValidWord(lower)) {
        throw std::invalid_argument("Word must contain only letters!");
    }

    if (!dictionary.contains(lower)) {
        throw std::invalid_argument("Word '" + word + "' not in dictionary!");
    }

    if (usedWords.find(lower) != usedWords.end()) {
        throw std::invalid_argument("Word '" + word + "' already used!");
    }

    if (lower[0] != requiredLetter) {
        throw std::invalid_argument("Word must start with letter '" +
                                    std::string(1, requiredLetter) + "'!");
    }

    return lower;
}

std::string HumanPlayer::getName() const {
    return name_;
}

ComputerPlayer::ComputerPlayer(std::string name) : name_(std::move(name)) {}

std::string ComputerPlayer::makeMove(char requiredLetter, const Dictionary& dictionary,
                                     const std::unordered_set<std::string>& usedWords) {
    std::string word = dictionary.getRandomUnusedWord(requiredLetter, usedWords);

    if (!word.empty() && usedWords.find(word) == usedWords.end()) {
        return word;
    }
    return "";
}

  

std::string ComputerPlayer::getName() const {
    return name_;
}