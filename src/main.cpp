/**
* @file main.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#include "../include/Common.hpp"
#include "../include/LinkedList.hpp"

int main() {
  Screen s{};
  LinkedList list {};
  
  std::size_t page     {1};
  std::size_t selectedD {1};

  char usrInput  {};

  bool isRunning {true};
  while(true) {
    list.printAll(s, page, selectedD, usrInput, isRunning);
    if(!isRunning) break;

    // Source - https://stackoverflow.com/a/32008479
    std::cout << "\033[2J\033[1;1H";

    s.print();

    std::cin >> usrInput;
    usrInput = std::tolower(usrInput);
    
    // flush the intput stream if it has an error
    if(std::cin.fail()) {
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  list.save();
  return 0;
}