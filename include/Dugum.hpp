#ifndef DUGUM
#define DUGUM
#include "Matris.hpp"

class LinkedList;

class Dugum {
public:
  Dugum() = default;

private:
  // this is just a place holder for the Matris class that I would have later
  
  // when we initialise m_matris it would initialise to a 10x10 matris
  Matris m_matris {};
  
  // these pointers are list initialised to nullptr
  Dugum* sonra {};
  Dugum* once  {};

  friend LinkedList;
  friend inline void printAll(const LinkedList& l);
  friend inline void print(const Dugum* l);
};

#endif