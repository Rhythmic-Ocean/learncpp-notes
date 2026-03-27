#include "Random.h"
#include <cstddef>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>

namespace WordList {
enum Words {
  mystry,
  broccoli,
  account,
  almost,
  spaghetti,
  opinion,
  beautiful,
  distance,
  luggage,
  word_count,
};

std::string_view enumToString(Words word) {
  switch (word) {
  case mystry:
    return "mystry";
  case broccoli:
    return "broccoli";
  case account:
    return "account";
  case almost:
    return "almost";
  case spaghetti:
    return "spaghetti";
  case opinion:
    return "opinion";
  case beautiful:
    return "beautiful";
  case distance:
    return "distance";
  case luggage:
    return "luggage";
  default:
    return "???";
  }
}
Words generate() {
  int num = Random::get(0, static_cast<int>(luggage));
  return static_cast<Words>(num);
}
} // namespace WordList

class Session {
  std::string m_word{};
  int m_wrong_chances{6};
  std::string m_dashes{};
  std::string m_guessed{};
  std::string m_wrongs{"++++++"};

public:
  Session(const std::string_view word)
      : m_word{word}, m_dashes(word.size(), '_') {}
  void putWrongs(char val) { m_wrongs[--m_wrong_chances] = val; }

  std::string_view getGuessed() { return m_guessed; }
  void putGuessed(char val) { m_guessed.push_back(val); }

  std::string_view getDashes() { return m_dashes; }
  void putDashes(char val, std::size_t pos) { m_dashes[pos] = val; }

  void welcomeComsole() {
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
    std::cout << std::endl;
  }

  void printComsole() {
    std::size_t dash_len{m_word.size()};
    std::cout << "The word: " << m_dashes;
    std::cout << "\tWrong guesses: " << m_wrongs << std::endl;
  }
};

bool errorCin() {
  if (!std::cin) {
    if (std::cin.eof()) {
      exit(0);
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return true;
  }
  return false;
}

int validateChar(char letter, std::string_view word, Session &session) {

  int counter{};
  std::string_view dashed = session.getDashes();
  for (auto i{0}; i < static_cast<int>(word.size()); i++) {
    if (word[i] == letter) {
      counter++;
      session.putDashes(letter, i);
    }
  }
  return counter;
}

int main() {
  char current_letter{};
  int letter_pos{};
  WordList::Words my_word = WordList::generate();
  std::string_view my_real_word = WordList::enumToString(my_word);
  Session session{my_real_word};
  std::string_view guessed = session.getGuessed();
  session.welcomeComsole();
  int chances{6};
  int correct_letters{};
  int to_be_correct_letters{static_cast<int>(my_real_word.size())};
  int valid_at_once{};
  while (chances > 0) {
    session.printComsole();
    std::cout << "Enter your next letter: ";
    std::cin >> current_letter;
    if (errorCin()) {
      std::cout << "Invalid input. Try again\n\n";
      continue;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (current_letter < 'a' || current_letter > 'z') {
      std::cout << "Invalid input. Try again\n\n";
      continue;
    }

    guessed = session.getGuessed();
    for (char i : guessed) {
      if (current_letter == i) {
        std::cout << "Letter already selected.\n";
        continue;
      }
    }
    session.putGuessed(current_letter);

    std::cout << "You entered : " << current_letter << std::endl;
    if ((valid_at_once = validateChar(current_letter, my_real_word, session)) !=
        0) {
      correct_letters += valid_at_once;
      if (correct_letters >= to_be_correct_letters) {
        std::cout << "You won!\n";
        return 0;
      }
      std::cout << "Yes, '" << current_letter << "' is in the word!\n\n";
    } else {
      session.putWrongs(current_letter);
      chances--;
      std::cout << "No, '" << current_letter << "' is NOT in the word!\n\n";
    }
  }
  std::cout << "You lost! The word was: " << my_real_word << std::endl;
}
