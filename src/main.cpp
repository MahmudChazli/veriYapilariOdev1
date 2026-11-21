/**
* @file main.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#include "../include/Common.hpp"
#include "../include/LinkedList.hpp"

int main() {
  Screen s{};
  LinkedList list {};

  
  std::size_t page {2};
  list.printD(s, page);

  std::size_t selected {6};
  list.printM(s, selected);
  s.print();

  
  return 0;
}