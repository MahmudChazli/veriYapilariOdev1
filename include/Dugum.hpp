/**
* @file Dugum.hpp
* @description iki yonlu Dugum ve matris iki yonlu bagli liste tutar
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


  Matris getMatris() { return matris; }

private:
  // when we initialise m_matris it would initialise to a 10x10 matris
  Matris matris {};

  // these pointers are list initialised to nullptr
  Dugum* sonra {};
  Dugum* once  {};

  friend LinkedList;
};

#endif