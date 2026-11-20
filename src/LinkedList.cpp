/**
* @file LinkedList.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#include "../include/linkedList.hpp"
#include <fstream>
#include <algorithm>



//-------------------------load---------------------------------


// this was easier than I thought
void LinkedList::load() {
  // Source - https://www.geeksforgeeks.org/cpp/how-to-read-from-a-file-in-cpp/
  std::ifstream f("kayitlar.txt");

  // Check if the file was opened successfully
  if (!f.is_open()) {
    std::cerr << "Error opening the file!";
    return;
  }

  std::string veri    {};

  // this is because I shouldn't give the last dugum a gec->sonra = new Dugum();
  std::size_t veriTRC {0}; // veri total row count
  while(std::getline(f, veri)) {
    ++veriTRC;
  }
  f.clear();
  f.seekg(0, std::ios::beg);

  std::size_t veriRC {1}; // veri row count
  Dugum* gec {m_ilk};
  while(std::getline(f, veri)) {

    std::size_t height {0};
    std::size_t width  {0};

    // this gives the end index of the string
    std::size_t endI {0};

    bool foundHW {true};
    // the for loop just makes it easier to manage without making unnecessary variables
    for(std::size_t start{0}; foundHW; ++endI) {
      if(veri[endI] == ' ') {

        if(!start){
          height = std::stoi(veri.substr(start, endI - start));

        } else {
          width  = std::stoi(veri.substr(start, endI - start));
          foundHW = false;
        };

        start = endI + 1;
      }
    }
    
    if(!gec->sonra) {
      if(veriRC < veriTRC){
        gec->sonra = new Dugum();
        gec->sonra->once = gec;  
      }
    }
    gec->matris.setHW(height, width);

    // it would be hard to read if I just merged both the for loops together
    for(std::size_t start {endI}; endI < veri.size(); ++endI) {
      if(veri[endI] == ' ') {

        gec->matris.push( std::stoi(veri.substr(start, endI - start)) );

        start = endI + 1;
      }
    }

    ++veriRC;
    gec = gec->sonra;
  }

  // Close the file
  f.close();
}



//-------------------------add----------------------------------



void LinkedList::add() {
  if(!m_ilk) {
    m_ilk = new Dugum();
  }
  Dugum* gec{m_ilk};
  
  while(gec->sonra) {
    gec = gec->sonra;
  }
  gec->sonra       = new Dugum();
  gec->sonra->once = gec;
}



//-------------------------remove----------------------------------



void LinkedList::remove() {
  if(!m_ilk) return;
  if(!m_ilk->sonra) {
    delete m_ilk;
    m_ilk = nullptr;
    return;
  }

  Dugum* gec{m_ilk};
  while(gec->sonra->sonra) {
    gec = gec->sonra;
  }
  delete gec->sonra;
  gec->sonra = nullptr;
}