#ifndef MATRIS
#define MATRIS
// include a random number generator file from learncpp.com

class Matris {
public:

  Matris() = default;  

  // this is for testing
  Matris(int m, int n) 
  : m_m {m}
  , m_n {n}
  {};

  // to print each matris we would need two for loops that's it
  void print();

private:
  int m_m {};
  int m_n {};

  // with this if we want to print the matris we would print every
  // column until !(i < m) and then we would go to the other row
  // (Source - https://stackoverflow.com/q/7684712)
  int* m_matris { new int[m_m * m_n] };

  // use the rand num generator here
  void generate();

};

#endif