/**
* @file Dugum.hpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#ifndef DUGUM
#define DUGUM
#include "Common.hpp"
#include "Matris.hpp"

class LinkedList;

class Dugum {
public:
  Dugum() = default;

private:
  // when we initialise m_matris it would initialise to a 10x10 matris
  Matris matris {};

  // these pointers are list initialised to nullptr
  Dugum* sonra {};
  Dugum* once  {};

  friend LinkedList;
};

#endif