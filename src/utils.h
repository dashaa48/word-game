/**
 * @file utils.h
 * @brief Вспомогательные функции для работы со строками
 */

#ifndef UTILS_H
#define UTILS_H

#include <string>

/**
 * @brief Преобразуем строку в нижний регистр
 * @param str Входная строка
 * @return Строка в нижнем регистре
 */
std::string toLower(const std::string& str);

/**
 * @brief Проверяет, содержит ли строка только буквы
 * @param str Входная строка
 * @return true, если слово корректно
 */
bool isValidWord(const std::string& str);

/**
 * @brief Возвращает последнюю значимую букву слова
 * @param word Входное слово
 * @return Последняя буква
 */
char getLastLetter(const std::string& word);

/**
 * @brief Возвращает предпоследнюю значимую букву слова
 * @param word Входное слово
 * @return Предпоследняя буква или '\0', если букв недостаточно
 */
char getSecondLastLetter(const std::string& word);

/**
 * @brief Возвращает предыдущую букву алфавита
 * @param c Текущая буква
 * @return Предыдущая буква или та же, если это 'a'
 */
char getPreviousLetter(char c);

#endif 