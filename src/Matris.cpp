/**
* @file Matris.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#include "../include/Common.hpp"
#include "../include/Matris.hpp"
#include <windows.h>



//--------------------------------delete---------------------------------------------



// column = 1 den height kadar gider
void Matris::deleteColumn(const std::size_t& column) {
  if(column <= 0 || column > m_width) throw std::out_of_range("Boyle bir sutun yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris should be deleted.
  assert(m_width > 1 && "the caller didn't delete the dugum before deleteColumn() was called");
  
  std::size_t deleteIndex {column - 1};

  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}; i < m_len; ++i) {

    // I thought this would be harder than just this
    if(i % m_width == deleteIndex) {
      MatrisDugum* sil {};
      if(i == 0) {
        sil = m_ilk;
        m_ilk = m_ilk->sonra;
        m_ilk->once = nullptr;
        gec = m_ilk;

      }else {
        sil = gec;
        MatrisDugum* sonra {gec->sonra};
        MatrisDugum* once  {gec->once};
        once->sonra = sonra;
        if(sonra) sonra->once = once;
        gec = sonra;
      }
      delete sil;
    }else {
      gec = gec->sonra;
    }
  }
  m_len -= m_height;
  --m_width; // we change the width since we deleted a column
}

// row = 1 den width kadar gider
void Matris::deleteRow(const int& row) {
  if(row <= 0 || row > m_height) throw std::out_of_range("Boyle bir satir yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris and the matris should be deleted.
  assert(m_height > 1 && "the caller didn't delete the dugum before deleteRow() was called");

  int deleteIndex {(row - 1) * (int)m_width}; 

  MatrisDugum* gec {m_ilk};
  for(int i{0}; i < m_len; ++i) {
    
    if(i >= deleteIndex && i < (deleteIndex + m_width)) {
      MatrisDugum* sil {gec};

      if(deleteIndex == 0) {
        gec = gec->sonra;
        m_ilk = gec;
        m_ilk->once = nullptr;

      }else {      
        gec->once->sonra = gec->sonra;
        if(gec->sonra) gec->sonra->once = gec->once;
        gec = gec->sonra;
      }
      delete sil;  
    }else {
      gec = gec->sonra;
    }
  }
  m_len -= m_width;
  --m_height; // we change the height since we deleted a row
}



//-------------------------------------swap------------------------------------------



// there is probably a better way to do this but this is the first thing that I could think of
// column starts from 1 till n
void Matris::columnSwap(const std::size_t& column1, const std::size_t& column2) {
  if(column1 <= 0 || column1 > m_width || column2 <= 0 || column2 > m_width) throw std::out_of_range("Boyle bir sutun yok.");

  std::size_t fIndex {column1 - 1}; // first column index
  std::size_t sIndex {column2 - 1}; // second column index

  int* fColumn {new int[m_height]};
  int* sColumn {new int[m_height]};

  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}, fI{0}, sI{0}; i < m_len; ++i) {

    if(i % m_width == fIndex) {
      fColumn[fI] = gec->get();
      ++fI;
    }

    if(i % m_width == sIndex) {
      sColumn[sI] = gec->get();
      ++sI;
    }

    gec = gec->sonra;
  }

  gec = m_ilk;

  for(std::size_t i{0}, fI{0}, sI{0}; i < m_len; ++i) {

    if(i % m_width == fIndex) {
      gec->push(sColumn[sI]);
      ++sI;
    }

    if(i % m_width == sIndex) {
      gec->push(fColumn[fI]);
      ++fI;
    }

    gec = gec->sonra;
  }
  delete[] fColumn;
  delete[] sColumn;
}

// row starts from 1 till n
void Matris::rowSwap(const int& row1, const int& row2) {
  if( row1 <= 0 || row1 > m_height || row2 <= 0 || row2 > m_height ) throw std::out_of_range("Boyle bir satir yok.");

  MatrisDugum* gec {m_ilk};

  int fIndex {(row1 - 1) * (int)m_width}; // first row index
  int sIndex {(row2 - 1) * (int)m_width}; // second row index

  int* fRow {new int[m_width]};
  int* sRow {new int[m_width]};

  // fI = first index; sI = second index;
  for(std::size_t i{0}, fI{0}, sI{0}; i < m_len; ++i) {
    if(i >= fIndex && i < (fIndex + (int)m_width)) {
      fRow[fI] = gec->get();
      ++fI;
    }
    if(i >= sIndex && i < (sIndex + (int)m_width)) {
      sRow[sI] = gec->get();
      ++sI;
    }
    gec = gec->sonra;
  }

  gec = m_ilk;

  // I think I could have done this better like
  // by adding another index variable in the previews 
  // for loop but that would hinder readability
  for(std::size_t i{0}, fI{0}, sI{0}; i < m_len; ++i) {
    if(i >= fIndex && i < (fIndex + (int)m_width)) {
      gec->push(sRow[sI]);
      ++sI;
    }

    if(i >= sIndex && i < (sIndex + (int)m_width)) {
      gec->push(fRow[fI]);
      ++fI;
    }
    gec = gec->sonra;
  }
  delete[] fRow;
  delete[] sRow;
}



//-------------------------------aritOrt---------------------------------------------



double Matris::aritOrt() const {
  MatrisDugum* gec {m_ilk};
  double sum {0};
  while(gec) {
    sum += gec->get();
    gec = gec->sonra;
  }
  return ( sum / m_len );
}



//--------------------------------push-----------------------------------------------



void Matris::push(const int& veri) {
  if(!m_ilk) {
    m_ilk = new MatrisDugum(veri);
  }else {
    MatrisDugum* gec {m_ilk};
    while(gec->sonra) {
      gec = gec->sonra;
    }
    gec->sonra = new MatrisDugum(veri);
  }
}



//-------------------------printM----------------------------------



// selected dugum is around 1 to 5
void Matris::print(Screen& s, const std::size_t& selectedD) {

  std::size_t paddingRow {3};
  std::size_t paddingCol {22};
  // times eight is just the dugum that it would be on
  std::size_t row {((selectedD - 1) % 5) * 8 + paddingRow};

  // this prints the arrows that show which dugum it currently has selected
  s.save(row,     paddingCol, "<-");
  s.save(row + 1, paddingCol, "<-");
  s.save(row + 2, paddingCol, "<-");
  s.save(row + 3, paddingCol, "<-");
  s.save(row + 4, paddingCol, "<-");
  s.save(row + 5, paddingCol, "<-");
  s.save(row + 6, paddingCol, "<-");

  paddingCol = 27;
  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}; i < m_height; ++i) {
    std::ostringstream oss {};
    for(std::size_t j {paddingCol}, times{0}; times < (m_width); j += 3, ++times) {
      s.save(row + i, j, std::to_string(gec->get()));

      gec = gec->sonra;
    }
  }
}



//--------------------------------generate-------------------------------------------



void Matris::generate() {
  m_ilk->push(Random::get(0, 99));

  // we already have the first variable in the list so we start at 1 for newLen
  std::size_t newLen {1};
  for(std::size_t i{0}; i < m_len; ++i) { // this is a timer (the teacher has different sizes of matris)

    // this would get us a number between 0 and 100 inclusive
    int num = Random::get(0, 99);

    MatrisDugum* gec{m_ilk};
    for(std::size_t j{0}; j < newLen; ++j) {
      if(num == gec->get()) break;
      if(j == newLen - 1) {
        gec->sonra = new MatrisDugum(num);
        gec->sonra->once = gec;
        ++newLen;
      }
      gec = gec->sonra;
    }
    gec = m_ilk;
  }
  m_height = m_width = static_cast<std::size_t>(std::floor(sqrt(m_len)));

  // we would delete the extra variables and make a kare matris
  MatrisDugum* gec {m_ilk};
  while(gec->sonra) {
    gec = gec->sonra;
  }
  for(std::size_t i{newLen}; i > m_height * m_width; --i) {
    MatrisDugum* sil {gec};
    gec = gec->once;
    gec->sonra = nullptr;
    delete sil;
  }
  m_len = m_height * m_width;
  
  // the teacher wanted an error case for this for some reason
  switch(m_len) {
  case 4:
  case 9:
  case 16:
  case 25:
  case 36:
  case 49:
  case 64:
  case 81:
  case 100:
    // nothing happens because it is a square matris
    break;
  default:
    // Source - https://stackoverflow.com/a/5182603
    // kare matris degil ise
    MessageBoxW(
      NULL, 
      L"Olusturulan Matris, Kare Matris Degildir!",
      L"Error!",
      MB_ICONEXCLAMATION | MB_OK
    );
    break;
  }
}