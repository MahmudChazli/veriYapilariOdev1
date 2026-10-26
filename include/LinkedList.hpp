#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>
#include <iomanip>
#include "Dugum.hpp"

class LinkedList {
public:
  LinkedList() = default;
  LinkedList(const int& matris) {
    m_ilk = new Dugum(matris);
  }

  using Matris = int;
  void add(Matris veri);
  void remove();
  Dugum* getOnce()  const { return m_ilk->once; }
  Dugum* getSonra() const { return m_ilk->sonra; }
  
  // in the futre I might change it to be a circular dynamic list
  // but for now it's only a two way dynamic list
  ~LinkedList() {
    Dugum* gec {m_ilk};
    Dugum* sil {};
    while(gec) {
      sil = gec;
      gec = gec->sonra;
      delete sil;
    }
  }

private:
  Dugum* m_ilk {};

  friend inline void printAll(LinkedList& l);
};

// took me a while to realise that all I needed to do for the
// print function to compile was add the inline keyword because of ODR
// (it's totaly my fault but still it's 1am and I don't want to take the blame)
inline void print(Dugum* d) {
  std::cout << std::setw(20);
  
  std::cout << "\n********************\n";
  std::cout << "* " << d->once << " *\n";
  std::cout << "--------------------\n";

  // I don't know what we are supposed to put here the teacher has it empty
  std::cout << "* " << " *\n"; 

  std::cout << "--------------------\n";
  std::cout << "* " << d->sonra << " *\n";
  std::cout << "--------------------\n";
}

inline void printAll(LinkedList& l) {
  Dugum* gec {l.m_ilk};
  while(gec) {
    print(gec);
    gec = gec->sonra;
  }
}

#endif