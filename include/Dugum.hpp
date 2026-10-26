#ifndef DUGUM
#define DUGUM

class LinkedList;

class Dugum {
public:
  Dugum() = default;
  Dugum(int matris) {
    m_matris = matris;
  }

private:
  // this is just a place holder for the Matris class that I would have later
  using Matris = int;
  Matris m_matris {};
  
  Dugum* sonra {};
  Dugum* once  {};

  friend LinkedList;
  friend inline void printAll(LinkedList& l);
  friend inline void print(Dugum* l);
};

#endif