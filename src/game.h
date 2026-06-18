/**
 * @file game.h
 * @brief Основная логика игры
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
 * @brief Режимы игры
 */
enum class GameMode {
    HUMAN_VS_PC,      ///< Человек против ПК
    TWO_HUMANS,       ///< Два человека
    TWO_HUMANS_VS_PC  ///< Два человека против ПК (по очереди)
};

/**
 * @class Game
 * @brief Управляет процессом игры
 */
class Game {
   public:
    /**
     * @brief Конструктор
     * @param mode Режим игры (HUMAN_VS_PC, TWO_HUMANS, TWO_HUMANS_VS_PC)
     * @param dictionaryPath Путь к папке с файлами словаря (a.txt, b.txt, etc)
     */
    Game(GameMode mode, const std::string& dictionaryPath);

    /**
     * @brief Запускает игровой цикл
     */
    void run();

    /**
     * @brief Возвращает последнее сыгранное слово
     * @return Последнее слово
     */
    std::string getLastWord() const;

    /**
     * @brief Возвращает текущую требуемую букву
     * @return Буква
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

#endif