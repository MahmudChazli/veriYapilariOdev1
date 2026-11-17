/**
* @file LinkedList.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

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