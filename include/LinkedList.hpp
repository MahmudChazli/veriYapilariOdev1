#ifndef LINKED_LIST
#define LINKED_LIST
#include "Common.hpp"
#include "Dugum.hpp"

class Matris;

class LinkedList {
public:
  LinkedList() {
    m_ilk = new Dugum();
  }

  void add();
  void remove();
  Dugum* getIlk() const { return m_ilk; };
  
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
};

// took me a while to realise that all I needed to do for the
// print function to compile was add the inline keyword because of ODR
// (it's totaly my fault but still it's 1am and I don't want to take the blame)
inline void print(const Dugum* d) {
  std::cout << std::right;
  std::cout << "\n********************\n";
  std::cout << "*  " << std::setw(13) << d << "   *\n";
  std::cout << "--------------------\n";

  // I don't know what we are supposed to put here the teacher has it empty
  std::cout << "* " << std::setw(19) << " *\n";

  std::cout << "--------------------\n";
  std::cout << "*  ";
  if(d->sonra) {
    std::cout << std::setw(13) << d->sonra;
  }
  else {
    std::cout << "0x0" << std::setw(15);
  }
  std::cout << "   *\n";
  std::cout << "********************\n";
}

inline void printAll(const LinkedList& l) {
  Dugum* gec {l.getIlk()};
  while(gec) {
    print(gec);
    gec = gec->sonra;
  }
}

#endif