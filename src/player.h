/**
 * @file player.h
 * @brief Классы игроков (человек и ПК)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_set>

#include "dictionary.h"

/**
 * @class Player
 * @brief Абстрактный базовый класс для игроков
 */
class Player {
   public:
    virtual ~Player() = default;

    /**
     * @brief Делает ход
     * @param requiredLetter Требуемая начальная буква
     * @param dictionary Словарь
     * @param usedWords Набор использованных слов
     * @return Сыгранное слово или пустая строка
     */
    virtual std::string makeMove(char requiredLetter, const Dictionary& dictionary,
                                 const std::unordered_set<std::string>& usedWords) = 0;

    /**
     * @brief Возвращает имя игрока
     * @return Имя
     */
    virtual std::string getName() const = 0;
};

/**
 * @class HumanPlayer
 * @brief Игрок-человек (ввод с клавиатуры)
 */
class HumanPlayer : public Player {
   public:
    /**
     * @brief Конструктор
     * @param name Имя игрока
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
 * @brief Игрок-ПК (случайный выбор слова)
 */
class ComputerPlayer : public Player {
   public:
    /**
     * @brief Конструктор
     * @param name Имя игрока ("PC")
     */
    explicit ComputerPlayer(std::string name = "PC");

    std::string makeMove(char requiredLetter, const Dictionary& dictionary,
                         const std::unordered_set<std::string>& usedWords) override;

    std::string getName() const override;

   private:
    std::string name_;
};

#endif