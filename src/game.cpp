#include "game.h"

#include <iostream>
#include <stdexcept>

#include "utils.h"

Game::Game(GameMode mode, const std::string& dictionaryPath)
    : mode_(mode), dictionary_(dictionaryPath), currentLetter_('a'), currentPlayerIndex_(0) {
    initializePlayers();
}

void Game::initializePlayers() {
    switch (mode_) {
        case GameMode::HUMAN_VS_PC:
            players_.push_back(std::make_unique<HumanPlayer>("Player"));
            players_.push_back(std::make_unique<ComputerPlayer>());
            break;
        case GameMode::TWO_HUMANS:
            players_.push_back(std::make_unique<HumanPlayer>("Player 1"));
            players_.push_back(std::make_unique<HumanPlayer>("Player 2"));
            break;
        case GameMode::TWO_HUMANS_VS_PC:
            players_.push_back(std::make_unique<HumanPlayer>("Player 1"));
            players_.push_back(std::make_unique<HumanPlayer>("Player 2"));
            players_.push_back(std::make_unique<ComputerPlayer>("PC"));
            break;
    }
}

void Game::run() {
    std::cout << "=== WORD GAME ===" << std::endl;
    std::cout << "Starting letter: '" << currentLetter_ << "'" << std::endl;

    while (true) {
        Player* current = players_[currentPlayerIndex_].get();
        std::cout << "\nTurn: " << current->getName() << " (letter: '" << currentLetter_ << "')"
                  << std::endl;

        try {
            std::string word = current->makeMove(currentLetter_, dictionary_, usedWords_);

            if (!word.empty()) {
                std::cout << current->getName() << " plays: " << word << std::endl;
            }

            if (word.empty()) {
                std::cout << current->getName() << " surrenders!" << std::endl;
                std::cout << "Winner: "
                          << players_[(currentPlayerIndex_ + 1) % players_.size()]->getName()
                          << std::endl;
                return;
            }

            usedWords_.insert(word);
            lastWord_ = word;
            currentLetter_ = getLastLetter(word);

            // Rule 5: search fallback letter inside previous word
            if (!dictionary_.hasAvailableWords(currentLetter_, usedWords_)) {
                std::string lower = toLower(lastWord_);

                for (int i = static_cast<int>(lower.size()) - 2; i >= 0; --i) {
                    char fallback = lower[i];

                    if (dictionary_.hasAvailableWords(fallback, usedWords_)) {
                        std::cout << "No words on '" << currentLetter_
                                  << "'! Switching to fallback letter '" << fallback << "'."
                                  << std::endl;

                        currentLetter_ = fallback;
                        break;
                    }
                }
            }

            std::cout << "Word accepted! Next letter: '" << currentLetter_ << "'" << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "ERROR: " << e.what() << std::endl;
            std::cout << current->getName() << " lost!" << std::endl;
            std::cout << "Winner: "
                      << players_[(currentPlayerIndex_ + 1) % players_.size()]->getName()
                      << std::endl;
            return;
        }

        nextPlayer();
    }
}

void Game::nextPlayer() {
    currentPlayerIndex_ = (currentPlayerIndex_ + 1) % players_.size();
}

bool Game::hasAvailableMoves() const {
    return dictionary_.hasAvailableWords(currentLetter_, usedWords_);
}

std::string Game::getLastWord() const {
    return lastWord_;
}

char Game::getCurrentLetter() const {
    return currentLetter_;
}