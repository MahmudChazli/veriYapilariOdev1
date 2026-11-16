#ifndef MATRIS
#define MATRIS
#include "Common.hpp"
#include "Random.h"
#include "MatrisDugum.hpp"

class Matris {
public:

  Matris(std::size_t height = 10, std::size_t width = 10) {
    // for now I'm just gonna use an assert to check the height and width
    assert(height <= 10 && width <= 10 && "height/width is above 10");
    assert(height >= 0 && width >= 0 && "height/width is negative");

    m_height = height;
    m_width  = width;
    m_len = height * width;
    generate(m_ilk, m_len, m_width, m_height);
  };

  // for the column delete we would add m_width after every deleted variable
  void deleteColumn(const std::size_t& column, MatrisDugum* &ilk, std::size_t& height, std::size_t& len);
  
  void deleteRow(const int& row, MatrisDugum* &ilk, int& width, std::size_t& len);

  void print();

  void test_print() {};

private:
  std::size_t m_height {};
  std::size_t m_width {};
  std::size_t m_len {m_height * m_width};

  MatrisDugum* m_ilk {};

  void generate(MatrisDugum* &ilk, std::size_t& len, std::size_t& width, std::size_t& height);
};

#endif