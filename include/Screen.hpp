#ifndef SCREEN
#define SCREEN

#include <iomanip>
#include <string_view>

class Screen {
public:
  Screen() {
    clearScreen();
  };

  void clearScreen();
  void save(const std::size_t& row, const std::size_t& col, std::string_view text);
  void print();

private:
  const std::size_t m_rowS {50};
  const std::size_t m_colS {100};
  char m_screen[50][100]; // initialize the screen with y = 50, x = 100

};

#endif