/**
* @file Screen.hpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#ifndef SCREEN
#define SCREEN

#include "Common.hpp"
#include <string_view>

class Screen {
public:
  Screen() {
    clear();
  };

  void clear();
  void save(const std::size_t& row, const std::size_t& col, std::string_view text);
  void print();

private:
  const std::size_t m_rowS {45};
  const std::size_t m_colS {100};
  char m_screen[45][100]; // initialize the screen with y = 50, x = 100

};

#endif