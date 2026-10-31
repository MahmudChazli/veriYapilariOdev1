#include "../include/Common.hpp"
#include "../include/Matris.hpp"

void Matris::generate(int* matris, std::size_t& len, std::size_t& width, std::size_t& height) {
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
    // some error case
    break;
  }
}