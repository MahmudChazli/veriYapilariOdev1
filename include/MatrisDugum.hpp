/**
* @file MatrisDugum.hpp
* @description Matris'in iki yonlu bagli listenin dugumu den olusur ve veri tutar
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#ifndef MATRISDUGUM
#define MATRISDUGUM

class Matris;

class MatrisDugum {
public:
  MatrisDugum() = default;
  MatrisDugum(const int& veri) : m_veri{veri} {};

  void push(const int& veri) { m_veri = veri; }
  int get() { return m_veri; };

private:
  MatrisDugum* sonra {};
  MatrisDugum* once  {};
  int m_veri {};

  friend Matris;
};

#endif