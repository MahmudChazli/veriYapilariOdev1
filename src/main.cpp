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
  std::size_t selected {1};

  char usrInput  {};

  bool isRunning {true};
  while(isRunning) {
    s.clear();

    // puts a separator at the start of the page
    s.save(1, 0, "--------------------------------------------------");

    
    list.printD(s, page);
    list.printM(s, selected);

    // puts a separated at the end of the page
    s.save(43, 0, "--------------------------------------------------");


    s.print();


    std::cin >> usrInput;
    
    // flush the intput stream if it has an error
    if(std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  
  return 0;
}