#ifndef MATRIS
#define MATRIS
#include "Random.h" // from learncpp.com

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

private:
  int m_m {10};
  int m_n {10};

  // with this if we want to print the matris we would print every
  // column until !(i < m) and then we would go to the other row
  // (Source - https://stackoverflow.com/q/7684712)
  int* m_matris { new int[m_m * m_n] };

  void generate() {
    int len {m_m * m_n};

    // this will be changed so that there wouldn't be any repeating numbers
    for(int i{}; i < len; ++i) {
      // this would get us a number between 0 and 100 inclusive
      m_matris[i] = Random::get(0, 100);
    }
  };

};

#endif