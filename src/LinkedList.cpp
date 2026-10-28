#include "../include/linkedList.hpp"

void LinkedList::add() {
  if(!m_ilk) {
    m_ilk = new Dugum();
  }
  Dugum* gec{m_ilk};
  
  while(gec->sonra) {
    gec = gec->sonra;
  }
  gec->sonra       = new Dugum();
  gec->sonra->once = gec;
}

void LinkedList::remove() {
  if(!m_ilk) return;
  if(!m_ilk->sonra) {
    delete m_ilk;
    m_ilk = nullptr;
    return;
  }

  Dugum* gec{m_ilk};
  while(gec->sonra->sonra) {
    gec = gec->sonra;
  }
  delete gec->sonra;
  gec->sonra = nullptr;
}