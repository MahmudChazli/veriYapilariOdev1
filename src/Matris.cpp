#include "../include/Common.hpp"
#include "../include/Matris.hpp"
#include <windows.h>

// column = 1 den height kadar gider
void Matris::deleteColumn(const std::size_t& column, MatrisDugum* &ilk, std::size_t& height, std::size_t& len) {
  if(column <= 0 || column > m_width) throw std::out_of_range("Boyle bir sutun yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris
  assert(m_width > 1 && "the caller didn't delete the dugum before deleteColumn() was called");
  
  std::size_t deleteIndex {column - 1};
  for(std::size_t i{0}; i < len; ++i) {
    MatrisDugum* gec {ilk};

    // I thought this would be harder than just this
    if(i % m_width != (deleteIndex)) {

      if(i == 0) {
        MatrisDugum* sil {ilk};
        ilk = ilk->sonra;
        delete sil;

      }else {
        MatrisDugum* sonra {gec->sonra};
        MatrisDugum* once  {gec->once};
        delete gec;
        once->sonra = sonra;
        sonra->once = once;
        gec = sonra;
      }
    }else {
      gec = gec->sonra;
    }
  }
  len -= height;
  --m_width;
}

// row = 1 den width kadar gider
void Matris::deleteRow(const int& row, MatrisDugum* &ilk, int& width, std::size_t& len) {
  if(row <= 0 || row > m_height) throw std::out_of_range("Boyle bir satir yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris
  assert(m_height > 1 && "the caller didn't delete the dugum before deleteRow() was called");

  int deleteIndex {(row - 1) * width}; 

  for(std::size_t i{0}; i < len; ++i) {
    MatrisDugum* gec {ilk};

    if(i >= (deleteIndex - 1) && i <= (deleteIndex + m_width - 1)) {
      if(deleteIndex == 0) {
        MatrisDugum* sil {gec};
        gec = gec->sonra;
        ilk = gec;
        ilk->once = nullptr;
        delete sil;

      }else {
        MatrisDugum* sonra = gec->sonra->sonra;
        delete gec->sonra;
        gec->sonra = sonra;
        sonra->once = gec;
      }
      
    }else {
      gec = gec->sonra;
    }
  }
  len -= width;
  --m_height;
}


void Matris::generate(MatrisDugum* &ilk, std::size_t& len, std::size_t& width, std::size_t& height) {
  ilk->push(Random::get(0, 99));

  std::size_t newLen {};
  for(std::size_t i{}; i < len; ++i) { // this is a timer (the teacher has different sizes of matris)

    // this would get us a number between 0 and 100 inclusive
    int num = Random::get(0, 99);

    for(std::size_t j{}; j <= newLen; ++j) {
      MatrisDugum* gec{ilk};
      if(j == newLen) {
        gec->sonra = new MatrisDugum(num);
        ++newLen;
      }
      if(num == gec->get()) break;
      gec = gec->sonra;
    }
  }
  len = newLen;
  height = width = static_cast<std::size_t>(std::ceil(sqrt(len)));

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