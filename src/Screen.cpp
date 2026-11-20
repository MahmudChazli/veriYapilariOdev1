#include "../include/Screen.hpp"
#include <iostream>



//--------------------------------clearScreen-------------------------------------



void Screen::clearScreen() {
  for(std::size_t i{0}; i < m_rowS; ++i) {
    for(std::size_t j{0}; j < m_colS; ++j) {
      m_screen[i][j] = ' ';
    }
  }
};



//--------------------------------save--------------------------------------------



void Screen::save(const std::size_t& row, const std::size_t& col, std::string_view text) {
  if(row >= m_rowS) throw std::out_of_range("ERROR save(row, col, text): satir limiti asti.");

  for(std::size_t i{0}; i < text.size(); ++i) {
    std::size_t saving {col + i};

    if(saving >= m_colS) throw std::out_of_range("ERROR save(row, col, text): sutun limiti asti.");

    m_screen[row][saving] = text[saving];
  }
}



//--------------------------------print-------------------------------------------



void Screen::print() {
  for(std::size_t i{0}; i < m_rowS; ++i) {
    for(std::size_t j{0}; j < m_colS; ++j) {
      std::cout << m_screen[i][j];
    }
    std::cout << '\n';
  }
};