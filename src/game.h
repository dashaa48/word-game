/**
 * @file game.h
 * @brief Main game logic
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <unordered_set>
#include <vector>

#include "dictionary.h"
#include "player.h"

/**
 * @enum GameMode
 * @brief Game modes
 */
enum class GameMode {
    HUMAN_VS_PC,      ///< Human vs computer
    TWO_HUMANS,       ///< Two humans
    TWO_HUMANS_VS_PC  ///< Two humans vs computer (alternating)
};

/**
 * @class Game
 * @brief Manages game flow
 */
class Game {
   public:
    /**
     * @brief Constructor
     * @param mode Game mode (HUMAN_VS_PC, TWO_HUMANS, TWO_HUMANS_VS_PC)
     * @param dictionaryPath Path to folder containing dictionary files (a.txt, b.txt, etc)
     */
    Game(GameMode mode, const std::string& dictionaryPath);

    /**
     * @brief Runs game loop
     */
    void run();

    /**
     * @brief Returns last played word
     * @return Last word
     */
    std::string getLastWord() const;

    /**
     * @brief Returns current required letter
     * @return Letter
     */
    char getCurrentLetter() const;

   private:
    GameMode mode_;
    Dictionary dictionary_;
    std::vector<std::unique_ptr<Player>> players_;
    std::unordered_set<std::string> usedWords_;
    std::string lastWord_;
    char currentLetter_;
    size_t currentPlayerIndex_;

    void initializePlayers();
    void nextPlayer();
    bool hasAvailableMoves() const;
};

#endif  // GAME_H