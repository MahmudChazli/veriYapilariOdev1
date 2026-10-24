#ifndef LINKED_LIST
#define LINKED_LIST
#include <iostream>
#include "Dugum.hpp"

class LinkedList {
public:
  LinkedList() = default;
  LinkedList(const int& matris) {
    m_ilk = new Dugum(matris);
  }

  void add();
  void remove();
  
  // in the futre I might change it to be two ways
  // but for now it's only a one way list
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
};

#endif