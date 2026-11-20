/**
* @file MatrisDugum.hpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
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