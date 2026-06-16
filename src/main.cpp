/**
 * @file main.cpp
 * @brief Entry point
 */

#include <filesystem>
#include <iostream>
#include <stdexcept>

#include "game.h"

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @brief Gets directory of executable file
 * @return Path to directory with .exe
 */
std::string getExeDirectory() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    std::string path(buffer);
    // Remove filename, keep directory
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
 * @brief Finds dictionary folder automatically
 * @return Path to dictionary
 */
std::string findDictionary() {
    std::string exeDir = getExeDirectory();

    // Try: same folder as exe
    std::string sameFolder = exeDir + "/dictionary";
    if (std::filesystem::exists(sameFolder)) {
        return sameFolder;
    }

    // Try: parent folder (when exe is in build/)
    std::string parentFolder = exeDir + "/../dictionary";
    if (std::filesystem::exists(parentFolder)) {
        return parentFolder;
    }

    // Default fallback
    return "dictionary";
}

/**
 * @brief Shows mode selection menu
 * @return Selected mode
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
 * @brief Asks for dictionary path (with auto-detect)
 * @return Path to dictionary folder
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