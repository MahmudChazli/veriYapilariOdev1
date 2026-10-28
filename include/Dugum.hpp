#ifndef DUGUM
#define DUGUM
#include "Matris.hpp"

class LinkedList;

class Dugum {
public:
  Dugum() = default;
  Dugum(Matris matris) {
    m_matris = matris;
  }

private:
  // this is just a place holder for the Matris class that I would have later
  
  Matris m_matris {};
  
  Dugum* sonra {};
  Dugum* once  {};

  friend LinkedList;
  friend inline void printAll(const LinkedList& l);
  friend inline void print(const Dugum* l);
};

#endif