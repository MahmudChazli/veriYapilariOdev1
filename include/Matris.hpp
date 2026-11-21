/**
* @file Matris.hpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#ifndef MATRIS
#define MATRIS
#include "Common.hpp"
#include "Random.h"
#include "MatrisDugum.hpp"
#include "Screen.hpp"

class Matris {
public:

  Matris(std::size_t height = 10, std::size_t width = 10) {
    // for now I'm just gonna use an assert to check the height and width
    assert(height <= 10 && width <= 10 && "height/width is above 10");

    m_height = height;
    m_width  = width;
    m_len    = height * width;
  };

  ~Matris() {
    while(m_ilk) {
      MatrisDugum* sil {m_ilk};
      m_ilk = m_ilk->sonra;
      delete sil;
    }
  }

  // for the column delete we would add m_width after every deleted variable and column start from 1 till n
  void deleteColumn(const std::size_t& column);
  
  // row starts from 1 till n
  void deleteRow(const int& row);

  // column starts from 1 till n
  void columnSwap(const std::size_t& column1, const std::size_t& column2);

  // row starts from 1 till n
  void rowSwap(const int& row1, const int& row2);

  // gives the aritmetik ortalama of the matris
  double aritOrt() const;

  void push(const int& veri);
  void print(Screen& s, const std::size_t& selectedD);

  void setHW(const std::size_t& height, const std::size_t& width) {
    m_height = height;
    m_width  = width;
    m_len    = height * width;
  }

  // generates the matris variables
  void generate();

private:
  std::size_t m_height {};
  std::size_t m_width  {};
  std::size_t m_len    {};

  MatrisDugum* m_ilk { new MatrisDugum() };
};

#endif