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
  while(isRunning) {
    s.clear();
    
    // Source - https://stackoverflow.com/a/32008479
    std::cout << "\033[2J\033[1;1H";

    
    // puts a separator at the start of the page
    s.save(1, 0, "--------------------------------------------------");

    
    list.printAll(s, page, selectedD, usrInput);


    // puts a separated at the end of the page
    s.save(43, 0, "--------------------------------------------------");

    s.print();

    std::cin >> usrInput;
    
    // flush the intput stream if it has an error
    if(std::cin.fail()) {
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    if(usrInput == 'k') {
      isRunning = false;
      // the command to save the list would run here as list.save();
    }
  }
  
  return 0;
}