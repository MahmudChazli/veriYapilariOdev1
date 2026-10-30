#ifndef MATRIS
#define MATRIS
#include "Random.h" // from learncpp.com
#include "Common.hpp"

class Matris {
public:

  Matris(int m = 10, int n = 10)
  : m_m {m}
  , m_n {n}
  {
    generate();
  };

  // to print each matris we would need two for loops that's it
  void print();
  
  void test_print() {
    std::cout << m_m << ' ' << m_n << '\n';
    std::cout << m_m * m_n << '\n';

    for(std::size_t i{}; i < m_len; ++i) {
      if(!(i % 10)) std::cout << '\n';
      std::cout << m_matris[i] << ' ';
    }
  };

private:
  std::size_t m_m {};
  std::size_t m_n {};
  std::size_t m_len {m_m * m_n};

  // with this if we want to print the matris we would print every
  // column until !(i < m) and then we would go to the other row
  // (Source - https://stackoverflow.com/q/7684712)
  int* m_matris { new int[m_m * m_n] };

  void generate() {

    std::size_t newLen {};
    for(std::size_t i{}; i < m_len; ++i) { // this is a timer (the teacher has different sizes of matris)

      // this would get us a number between 0 and 100 inclusive
      int num = Random::get(1, 100);

      for(std::size_t j{}; j <= newLen; ++j) {
        if(j == newLen) {
          m_matris[j] = num;
          ++newLen;
        }
        if(num == m_matris[j]) break;
      }
    }
    m_len = newLen;
  };

};

#endif