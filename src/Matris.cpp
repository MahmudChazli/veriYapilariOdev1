#include "../include/Common.hpp"
#include "../include/Matris.hpp"
#include <windows.h>

// column = 1 den height kadar gider
void Matris::deleteColumn(const std::size_t& column, MatrisDugum* &ilk, const std::size_t& height, std::size_t& len) {
  if(column <= 0 || column > m_width) throw std::out_of_range("Boyle bir sutun yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris should be deleted.
  assert(m_width > 1 && "the caller didn't delete the dugum before deleteColumn() was called");
  
  std::size_t deleteIndex {column - 1};

  MatrisDugum* gec {ilk};
  for(std::size_t i{0}; i < len; ++i) {

    // I thought this would be harder than just this
    if(i % m_width == deleteIndex) {
      MatrisDugum* sil {};
      if(i == 0) {
        sil = ilk;
        ilk = ilk->sonra;
        ilk->once = nullptr;
        gec = ilk;

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
  len -= height;
  --m_width; // we change the width since we deleted a column
}

// row = 1 den width kadar gider
void Matris::deleteRow(const int& row, MatrisDugum* &ilk, const int& width, std::size_t& len) {
  if(row <= 0 || row > m_height) throw std::out_of_range("Boyle bir satir yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris and the matris should be deleted.
  assert(m_height > 1 && "the caller didn't delete the dugum before deleteRow() was called");

  int deleteIndex {(row - 1) * width}; 

  MatrisDugum* gec {ilk};
  for(int i{0}; i < len; ++i) {
    
    if(i >= deleteIndex && i < (deleteIndex + width)) {
      MatrisDugum* sil {gec};

      if(deleteIndex == 0) {
        gec = gec->sonra;
        ilk = gec;
        ilk->once = nullptr;

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
  len -= width;
  --m_height; // we change the height since we deleted a row
}

// there is probably a better way to do this but this is the first thing that I could think of
// column starts from 1 till n
void Matris::columnSwitch(const std::size_t& column1, const std::size_t& column2, const std::size_t& len) {
  if(column1 <= 0 || column1 > m_width || column2 <= 0 || column2 > m_width) throw std::out_of_range("Boyle bir sutun yok.");

  std::size_t fIndex {column1 - 1}; // first column index
  std::size_t sIndex {column2 - 1}; // second column index

  int* fColumn {new int[m_height]};
  int* sColumn {new int[m_height]};

  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}, fI{0}, sI{0}; i < len; ++i) {

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

  for(std::size_t i{0}, fI{0}, sI{0}; i < len; ++i) {

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
void Matris::rowSwitch(const int& row1, const int& row2, const int& width, const std::size_t& len) {
  if( row1 <= 0 || row1 > m_height || row2 <= 0 || row2 > m_height ) throw std::out_of_range("Boyle bir satir yok.");

  MatrisDugum* gec {m_ilk};

  int fIndex {(row1 - 1) * width}; // first row index
  int sIndex {(row2 - 1) * width}; // second row index

  int* fRow {new int[width]};
  int* sRow {new int[width]};

  // fI = first index; sI = second index;
  for(std::size_t i{0}, fI{0}, sI{0}; i < len; ++i) {
    if(i >= fIndex && i < (fIndex + width)) {
      fRow[fI] = gec->get();
      ++fI;
    }
    if(i >= sIndex && i < (sIndex + width)) {
      sRow[sI] = gec->get();
      ++sI;
    }
    gec = gec->sonra;
  }

  gec = m_ilk;

  // I think I could have done this better like
  // by adding another index variable in the previews 
  // for loop but that would hinder readability
  for(std::size_t i{0}, fI{0}, sI{0}; i < len; ++i) {
    if(i >= fIndex && i < (fIndex + width)) {
      gec->push(sRow[sI]);
      ++sI;
    }

    if(i >= sIndex && i < (sIndex + width)) {
      gec->push(fRow[fI]);
      ++fI;
    }
    gec = gec->sonra;
  }
  delete[] fRow;
  delete[] sRow;
}

void Matris::generate(MatrisDugum* &ilk, std::size_t& len, std::size_t& width, std::size_t& height) {
  ilk->push(Random::get(0, 99));

  // we already have the first variable in the list so we start at 1 for newLen
  std::size_t newLen {1};
  for(std::size_t i{0}; i < len; ++i) { // this is a timer (the teacher has different sizes of matris)

    // this would get us a number between 0 and 100 inclusive
    int num = Random::get(0, 99);

    MatrisDugum* gec{ilk};
    for(std::size_t j{0}; j < newLen; ++j) {
      if(num == gec->get()) break;
      if(j == newLen - 1) {
        gec->sonra = new MatrisDugum(num);
        gec->sonra->once = gec;
        ++newLen;
      }
      gec = gec->sonra;
    }
    gec = ilk;
  }
  len = newLen;
  height = width = static_cast<std::size_t>(std::floor(sqrt(len)));

  // kare matris yapmak satir sutun silmeleri ve yer degistirmede daha rahat olur
  MatrisDugum* gec {ilk};
  while(gec->sonra) {
    gec = gec->sonra;
  }
  for(std::size_t i{len}; i > height * width; --i) {
    MatrisDugum* sil {gec};
    gec = gec->once;
    gec->sonra = nullptr;
    delete sil;
  }
  len = height * width;
  
  // the teacher wanted an error case for this for some reason
  switch(len) {
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