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
  MatrisDugum(const int& ver) : m_ver{ver} {};

  void push(const int& ver) { m_ver = ver; }
  int get() { return m_ver; };

private:
  MatrisDugum* sonra {};
  MatrisDugum* once  {};
  int m_ver {};

  friend Matris;
};

#endif