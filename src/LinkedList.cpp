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
#include <string>
#include <sstream>



//-------------------------load---------------------------------


// this was easier than I thought
void LinkedList::load() {
  // Source - https://www.geeksforgeeks.org/cpp/how-to-read-from-a-file-in-cpp/
  std::ifstream f("src/kayitlar.txt");

  // Check if the file was opened successfully
  if (!f.is_open()) {
    std::cerr << "Error load(): kayitlar.txt didn't open.";
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



//-------------------------printD----------------------------------


// I called it list page it's just that the teacher wants us to print five
// at a time so each five would be a page. listPage = 1 till n
void LinkedList::printD(Screen& s, const std::size_t& listPage) {
  float listLen {0}; // list length
  
  Dugum* gec {m_ilk};
  while(gec) {
    ++listLen;
    gec = gec->sonra;
  }
  gec = m_ilk;
  listLen = std::ceil(listLen / 5);
  if(listPage > listLen || listPage == 0) throw std::out_of_range("Error printD(s, listPage): page out of range.");

  std::ostringstream oss {};
  std::size_t listPageLen = (listPage - 1) * 5;
  // this moves gec to where it needs to be
  for(std::size_t i{0}; i < listPageLen; ++i) gec = gec->sonra;

  for(std::size_t i{listPageLen}, row{3}, col{0}; gec && i < (listPageLen + 5); ++i, row += 8) {

    // this clears the ostringstream
    oss.str("");
    oss.clear();
    oss << gec;
    std::string currAd {oss.str()};


    oss.str("");
    oss.clear();

    oss << std::fixed << std::setprecision(2);
    oss << gec->matris.aritOrt();
    std::string aritOrt {oss.str()};
    
    oss.str("");
    oss.clear();

    std::string goToAd {};
    if(gec->sonra) {
      oss << gec->sonra;
      goToAd = oss.str();
    }else{
      goToAd = "0x0";
    }

    s.save(row, col, "********************");

    // saving own address------------------------------------------
    s.save(row + 1, col, "*");
    s.save(row + 1, col + 3, currAd);
    s.save(row + 1, col + 19, "*");
    //-------------------------------

    s.save(row + 2, col, "--------------------");

    // saving aritOrt of matris------------------------------------
    s.save(row + 3, col, "*");
    s.save(row + 3, col + 7, aritOrt);
    s.save(row + 3, col + 19, "*");
    //-------------------------------------------------------------

    s.save(row + 4, col, "--------------------");

    // go to address-----------------------------------------------
    s.save(row + 5, col, "*");
    s.save(row + 5, col + 3, goToAd);
    s.save(row + 5, col + 19, "*");
    //-------------------------------------------------------------

    s.save(row + 6, col, "********************");
    
    gec = gec->sonra;
  }
}