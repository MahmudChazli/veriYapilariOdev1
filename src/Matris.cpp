#include "../include/Common.hpp"
#include "../include/Matris.hpp"
#include <windows.h>

// column = 1 den height kadar gider
void Matris::deleteColumn(const std::size_t& column, int* &matris, std::size_t& height, std::size_t& len) {
  if(column <= 0 || column > m_width) throw std::out_of_range("Boyle bir sutun yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris
  assert(m_width > 1 && "the caller didn't delete the dugum before deleteColumn() was called");
  
  std::size_t deleteIndex {column - 1};
  int* new_matris {new int[len - height]};
  for(std::size_t i{0}, newMatrisIndex{0}; i < len; ++i) {

    // I thought this would be harder than just this
    if(i % m_width != deleteIndex) {
      new_matris[newMatrisIndex] = matris[i];
      ++newMatrisIndex;
    }
  }
  delete[] matris;
  matris = new_matris;
  len   -= height;
  --m_width;
}

// row = 1 den width kadar gider
void Matris::deleteRow(const std::size_t& row, int* &matris, std::size_t& width, std::size_t& len) {
  if(row <= 0 || row > m_height) throw std::out_of_range("Boyle bir satir yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris
  assert(m_height > 1 && "the caller didn't delete the dugum before deleteRow() was called");

  std::size_t deleteIndex {(row - 1) * width}; 
  int* new_matris {new int[len - width]};

  for(std::size_t i{0}, newMatrisIndex{0}; i < len; ++i) {

    // don't add the row that we want to delete
    if(i < deleteIndex || i > (deleteIndex + m_width - 1)) {
      new_matris[newMatrisIndex] = matris[i];
      ++newMatrisIndex;
    }
  }
  delete[] matris;
  matris = new_matris;
  len   -= width;
  --m_height;
}


void Matris::generate(int* &matris, std::size_t& len, std::size_t& width, std::size_t& height) {
  std::size_t newLen {};
  for(std::size_t i{}; i < len; ++i) { // this is a timer (the teacher has different sizes of matris)

    // this would get us a number between 0 and 100 inclusive
    int num = Random::get(0, 99);

    for(std::size_t j{}; j <= newLen; ++j) {
      if(j == newLen) {
        matris[j] = num;
        ++newLen;
      }
      if(num == matris[j]) break;
    }
  }
  len = newLen;
  height = width = static_cast<std::size_t>(std::ceil(sqrt(len)));

  // this could be made into a helper function
  int* new_matris { new int[len] };
  for(std::size_t i{}; i < len; ++i) {
    new_matris[i] = matris[i];
  }
  delete[] matris;
  matris = new_matris;

  // I'll do this later (I'm not sure what I need to do here)
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