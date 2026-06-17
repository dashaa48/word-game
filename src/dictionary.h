/**
 * @file dictionary.h
 * @brief Класс словаря, для хранения слов
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <unordered_set>
#include <vector>

/**
 * @class Dictionary
 * @brief Загружает и хранит слова из текстовых файлов
 */
class Dictionary {
   public:
    /**
     * @brief Конструктор
     * @param dictionaryPath Путь к папке словаря
     */
    explicit Dictionary(const std::string& dictionaryPath);

    /**
     * @brief Проверяет, есть ли слово в словаре (без учета регистра)
     * @param word Слово для проверки (любой регистр: "APPLE", "apple")
     * @return true если слово есть в файлах словаря
     */
    bool contains(const std::string& word) const;

    /**
     * @brief Получение случайного слово, начинающееся с заданной буквы
     * @param letter Начальная буква
     * @return Слово или пустая строка, если таких нет
     */
    std::string getRandomWord(char letter) const;

    /**
     * @brief Получаем случайное неиспользованное слово, начинающееся с заданной буквы
     * @param letter Начальная буква
     * @param usedWords Уже использованные слова
     * @return Неиспользованное слово или пустая строка, если таких нет
     */
    std::string getRandomUnusedWord(char letter,
                                    const std::unordered_set<std::string>& usedWords) const;

    /**
     * @brief Проверяет наличие неиспользованных слов для заданной буквы
     * @param letter Буква для проверки
     * @param usedWords Набор уже использованных слов
     * @return true, если есть доступные слова
     */
    bool hasAvailableWords(char letter, const std::unordered_set<std::string>& usedWords) const;

   private:
    static constexpr int ALPHABET_SIZE = 26;

    std::string path_;
    std::unordered_set<std::string> allWords_;
    std::vector<std::string> wordsByLetter_[ALPHABET_SIZE];  

    static int letterToIndex(char c);
    void loadLetterFile(char letter);
};

#endif  