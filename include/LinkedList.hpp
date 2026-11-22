/**
* @file LinkedList.hpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#ifndef LINKED_LIST
#define LINKED_LIST
#include "Dugum.hpp"
#include "Screen.hpp"

class Matris;

class LinkedList {
public:
  LinkedList() {
    m_ilk = new Dugum();
    load();
  }
  // in the futre I might change it to be a circular dynamic list
  // but for now it's only a two way dynamic list
  ~LinkedList() {
    Dugum* gec {m_ilk};
    while(gec) {
      Dugum* sil {gec};
      gec = gec->sonra;
      delete sil;
    }
  }

  void load();
  void save();
  void addLower(const std::size_t& selectedD);
  void addUpper(std::size_t& selectedD);
  
  void remove(Dugum* gec);

  std::size_t getLen();

  // orders the list according to aritOrt
  void orderL();

  // print Dugum
  void printD(Screen& s, const std::size_t& listPage);

  // print matris
  void printMatris(Screen& s, const std::size_t& selectedD);

  void printMD(Screen& s, const std::size_t listPage, const std::size_t& selectedD);

  void printMenu(Screen& s);

  void printAll(Screen& s, std::size_t& listPage, std::size_t& selectedD, const char& usrInput, bool& isRunning);
  
  Dugum* getIlk() const { return m_ilk; };

private:
  Dugum* m_ilk {};
};

#endif