#ifndef MATRIS
#define MATRIS
#include "Common.hpp"
#include "Random.h"

class Matris {
public:

  Matris(std::size_t height = 10, std::size_t width = 10)
  : m_height {height}
  , m_width {width}
  {
    generate(m_matris, m_len, m_width);
  };

  void print();

  void test_print() {
    std::cout << m_height << ' ' << m_width << '\n';
    std::cout << m_len << '\n';

    for(std::size_t i{}; i < m_len; ++i) {
      if(!(i % m_width)) std::cout << '\n';
      std::cout << m_matris[i] << ' ';
    }
  };

private:
  std::size_t m_height {};
  std::size_t m_width {};
  std::size_t m_len {m_height * m_width};

  // (Source - https://stackoverflow.com/q/7684712)
  int* m_matris { new int[m_len] };

  void generate(int* matris, std::size_t& len, std::size_t& width);
};

#endif