/**
 * @file test_game.cpp
 * @brief Tests for the game (doctest)
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "dictionary.h"
#include "game.h"
#include "player.h"
#include "utils.h"

#include <filesystem>
#include <fstream>
#include <sstream>

// ===== Utils tests =====

TEST_CASE("toLower converts to lowercase") {
    CHECK(toLower("HELLO") == "hello");
    CHECK(toLower("World") == "world");
    CHECK(toLower("abc") == "abc");
}

TEST_CASE("getLastLetter returns last character") {
    CHECK(getLastLetter("hello") == 'o');
    CHECK(getLastLetter("abc") == 'c');
}

TEST_CASE("getSecondLastLetter returns second last character") {
    CHECK(getSecondLastLetter("hello") == 'l');
    CHECK(getSecondLastLetter("ab") == 'a');
}

// ===== Dictionary tests =====

TEST_CASE("Dictionary loads words from files") {
    std::filesystem::create_directories("test_dict");
    std::ofstream("test_dict/a.txt") << "apple\napricot\n";
    std::ofstream("test_dict/b.txt") << "banana\nberry\n";

    Dictionary dict("test_dict");

    CHECK(dict.contains("apple"));
    CHECK(dict.contains("banana"));
    CHECK_FALSE(dict.contains("unknown"));

    std::filesystem::remove_all("test_dict");
}

TEST_CASE("Dictionary returns random word") {
    std::filesystem::create_directories("test_dict2");
    std::ofstream("test_dict2/a.txt") << "apple\napricot\n";

    Dictionary dict("test_dict2");
    std::string word = dict.getRandomWord('a');

    CHECK((word == "apple" || word == "apricot"));

    std::filesystem::remove_all("test_dict2");
}

TEST_CASE("Dictionary checks available words") {
    std::filesystem::create_directories("test_dict3");
    std::ofstream("test_dict3/a.txt") << "apple\n";

    Dictionary dict("test_dict3");
    std::unordered_set<std::string> used;

    CHECK(dict.hasAvailableWords('a', used));
    used.insert("apple");
    CHECK_FALSE(dict.hasAvailableWords('a', used));

    std::filesystem::remove_all("test_dict3");
}

// ===== Player tests =====

TEST_CASE("ComputerPlayer returns word from dictionary") {
    std::filesystem::create_directories("test_dict4");
    std::ofstream("test_dict4/a.txt") << "apple\n";

    Dictionary dict("test_dict4");
    ComputerPlayer pc;
    std::unordered_set<std::string> used;

    std::string word = pc.makeMove('a', dict, used);
    CHECK(word == "apple");

    std::filesystem::remove_all("test_dict4");
}

// ===== Game tests =====

TEST_CASE("Game starts with initial letter 'a'") {
    std::filesystem::create_directories("test_dict5");
    std::ofstream("test_dict5/a.txt") << "apple\n";

    Game game(GameMode::HUMAN_VS_PC, "test_dict5");
    CHECK(game.getCurrentLetter() == 'a');

    std::filesystem::remove_all("test_dict5");
}
TEST_CASE("Dictionary does not contain unknown words") {
    std::filesystem::create_directories("test_dict6");
    std::ofstream("test_dict6/a.txt") << "apple\n";

    Dictionary dict("test_dict6");
    CHECK_FALSE(dict.contains("unknown"));
    CHECK_FALSE(dict.contains(""));

    std::filesystem::remove_all("test_dict6");
}

TEST_CASE("Game handles empty dictionary gracefully") {
    std::filesystem::create_directories("test_dict7");

    Game game(GameMode::HUMAN_VS_PC, "test_dict7");
    CHECK(game.getCurrentLetter() == 'a');

    std::filesystem::remove_all("test_dict7");
}
// ===== Negative scenarios =====

TEST_CASE("isValidWord rejects invalid and accepts valid input") {
    CHECK(isValidWord("hello"));             // letters
    CHECK(isValidWord("Apple"));             // register
    CHECK_FALSE(isValidWord(""));            // empty line
    CHECK_FALSE(isValidWord("hello123"));    // numbers
    CHECK_FALSE(isValidWord("hello world")); // blank
    CHECK_FALSE(isValidWord("abc!"));        // special characters
}

TEST_CASE("Dictionary handles missing letter files gracefully") {
    std::filesystem::create_directories("test_dict_missing");
    std::ofstream("test_dict_missing/a.txt") << "apple\n";

    Dictionary dict("test_dict_missing");

    CHECK_FALSE(dict.contains("banana")); 
    CHECK(dict.getRandomWord('z') == ""); 
    CHECK_FALSE(dict.hasAvailableWords('z', {}));

    std::filesystem::remove_all("test_dict_missing");
}

TEST_CASE("ComputerPlayer surrenders when all words used") {
    std::filesystem::create_directories("test_dict_surrender");
    std::ofstream("test_dict_surrender/a.txt") << "apple\n";

    Dictionary dict("test_dict_surrender");
    ComputerPlayer pc;
    std::unordered_set<std::string> used;
    used.insert("apple"); 

    std::string word = pc.makeMove('a', dict, used);
    CHECK(word == ""); // for rent

    std::filesystem::remove_all("test_dict_surrender");
}

TEST_CASE("getSecondLastLetter returns correct letter for fallback") {
    CHECK(getSecondLastLetter("apple") == 'l');  // a-p-p-l-e → 'l'
    CHECK(getSecondLastLetter("banana") == 'n'); // b-a-n-a-n-a → 'n' 
    CHECK(getSecondLastLetter("hi") == 'h');     // h-i → 'h'
    CHECK(getSecondLastLetter("a") == 'a');      // 1 letter → the same letter
    CHECK(getSecondLastLetter("") == '\0');      // '\0'
}

TEST_CASE("Game starts with letter 'a' even with empty dictionary") {
    std::filesystem::create_directories("test_dict_empty");

    Game game(GameMode::HUMAN_VS_PC, "test_dict_empty");
    CHECK(game.getCurrentLetter() == 'a'); 

    std::filesystem::remove_all("test_dict_empty");
}
TEST_CASE("HumanPlayer throws exception on invalid word") {
    std::filesystem::create_directories("test_dict_ex");

    std::ofstream("test_dict_ex/a.txt") << "apple\n";

    Dictionary dict("test_dict_ex");

    HumanPlayer player("Tester");

    std::unordered_set<std::string> used;

    std::istringstream input("123abc\n");
    std::cin.rdbuf(input.rdbuf());

    CHECK_THROWS_AS(
        player.makeMove('a', dict, used),
        std::invalid_argument
    );

    std::filesystem::remove_all("test_dict_ex");
}