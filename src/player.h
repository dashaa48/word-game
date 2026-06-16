/**
 * @file player.h
 * @brief Player classes (human and computer)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_set>

#include "dictionary.h"

/**
 * @class Player
 * @brief Abstract base class for players
 */
class Player {
   public:
    virtual ~Player() = default;

    /**
     * @brief Makes a move
     * @param requiredLetter Required starting letter
     * @param dictionary Dictionary
     * @param usedWords Set of used words
     * @return Played word or empty string
     */
    virtual std::string makeMove(char requiredLetter, const Dictionary& dictionary,
                                 const std::unordered_set<std::string>& usedWords) = 0;

    /**
     * @brief Gets player name
     * @return Name
     */
    virtual std::string getName() const = 0;
};

/**
 * @class HumanPlayer
 * @brief Human player (keyboard input)
 */
class HumanPlayer : public Player {
   public:
    /**
     * @brief Constructor
     * @param name Player name
     */
    explicit HumanPlayer(std::string name);

    std::string makeMove(char requiredLetter, const Dictionary& dictionary,
                         const std::unordered_set<std::string>& usedWords) override;

    std::string getName() const override;

   private:
    std::string name_;
};

/**
 * @class ComputerPlayer
 * @brief Computer player (random word selection)
 */
class ComputerPlayer : public Player {
   public:
    /**
     * @brief Constructor
     * @param name Player name (default "PC")
     */
    explicit ComputerPlayer(std::string name = "PC");

    std::string makeMove(char requiredLetter, const Dictionary& dictionary,
                         const std::unordered_set<std::string>& usedWords) override;

    std::string getName() const override;

   private:
    std::string name_;
};

#endif  // PLAYER_H