/**
 * @file main.cpp
 * @brief Точка входа
 */

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "game.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Определяет папку, в которой находится исполняемый файл
 * @return Путь к директорию с программой или "." в случае ошибки
 */
std::string getExeDirectory() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string path(buffer);
    // Убираем имя файла, оставляем только папку
    size_t lastSlash = path.find_last_of("\\/");
    if (lastSlash != std::string::npos) {
        return path.substr(0, lastSlash);
    }
    return ".";
#else
    return ".";
#endif
}

/**
 * @brief Автоматически находит папку со словарём
 * @return Путь к папке словаря
 */
std::string findDictionary() {
    std::string exeDir = getExeDirectory();

    // Пробуем: та же папка, что и .exe
    std::string sameFolder = exeDir + "/dictionary";
    if (std::filesystem::exists(sameFolder)) {
        return sameFolder;
    }

    // Ищем в родительской папке (если .exe в build/)
    std::string parentFolder = exeDir + "/../dictionary";
    if (std::filesystem::exists(parentFolder)) {
        return parentFolder;
    }

    // Вариант по умолчанию
    return "dictionary";
}

/**
 * @brief Показывает меню выбора режима игры
 * @return Выбранный режим
 */
#include <limits>

GameMode selectMode() {
    std::cout << "=== WORD GAME ===" << std::endl;
    std::cout << "Select mode:" << std::endl;
    std::cout << "1. Human vs PC" << std::endl;
    std::cout << "2. Two humans" << std::endl;
    std::cout << "3. Two humans vs PC" << std::endl;

    while (true) {
        std::cout << "Your choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                return GameMode::HUMAN_VS_PC;
            case 2:
                return GameMode::TWO_HUMANS;
            case 3:
                return GameMode::TWO_HUMANS_VS_PC;
            default:
                std::cout << "Invalid choice. Please enter 1, 2 or 3." << std::endl;
        }
    }
}

/**
 * @brief Запрашивает путь к словарю (с автоопределением)
 * @return Путь к папке словаря
 */
std::string getDictionaryPath() {
    std::string autoPath = findDictionary();
    std::cout << "Enter dictionary path (Enter for '" << autoPath << "'): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty()) {
        return autoPath;
    }
    return path;
}

int main(int argc, char* argv[]) {
    try {
        std::string dictPath = (argc > 1) ? argv[1] : getDictionaryPath();
        GameMode mode = selectMode();

        Game game(mode, dictPath);
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}