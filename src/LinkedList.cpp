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
#include <windows.h>



//-------------------------load---------------------------------


// this was easier than I thought
void LinkedList::load() {
  // Source - https://www.geeksforgeeks.org/cpp/how-to-read-from-a-file-in-cpp/
  std::ifstream f("lib/kayitlar.txt");

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



//-------------------------addLower---------------------------------



// the checks for selectedD are done by the parent caller
void LinkedList::addLower(const std::size_t& selectedD) {
  Dugum* gec{m_ilk};

  if(!gec) {
    gec = new Dugum();
  }else {

    std::size_t len {getLen()};

    // this is here so that if the parent forgot to do the check we would throw an error
    if(selectedD > len || selectedD < 1) throw std::out_of_range("Error addUppoer(selectedD): selectedD out of range");

    for(std::size_t i{1}; i < selectedD; ++i) {
      gec = gec->sonra;
    }

    Dugum* sonra = gec->sonra;

    gec->sonra = new Dugum();
    gec->sonra->once = gec;

    // if once exists
    if(sonra) {
      sonra->once = gec->sonra;
      gec->sonra->sonra = sonra;
    }
  }

  gec->sonra->matris.generate();
}



//-------------------------addUpper---------------------------------



// the checks for selectedD are done by the parent caller
void LinkedList::addUpper(std::size_t& selectedD) {
  Dugum* gec{m_ilk};

  if(!gec) {
    gec = new Dugum();

  }else {
    std::size_t len {getLen()};

    // this is here so that if the parent forgot to do the check we would throw an error
    if(selectedD > len || selectedD < 1) throw std::out_of_range("Error addUppoer(selectedD): selectedD out of range");

    for(std::size_t i{1}; i < selectedD; ++i) {
      gec = gec->sonra;
    }

    Dugum* once = gec->once;

    gec->once = new Dugum();
    gec->once->sonra = gec;

    // if once exists
    if(once) {
      once->sonra = gec->once;
      gec->once->once = once;

    }else { // this would mean that we added a upper node to m_ilk
      m_ilk = gec->once;
    }
  }
  gec->once->matris.generate();
}



//-------------------------remove----------------------------------



void LinkedList::remove(Dugum* gec) {
  if(gec == m_ilk) {
    if(!gec->sonra) {
      MessageBoxW(
        NULL, 
        L"En az bir matris olmak zorunlu.",
        L"Error!",
        MB_ICONEXCLAMATION | MB_OK
      );
      return;
    }
    m_ilk = gec->sonra;
  }
  Dugum* sonra {gec->sonra};
  Dugum* once  {gec->once};

  if(once)
    once->sonra = sonra;

  if(sonra)
    sonra->once = once;

  delete gec;
}



//-------------------------getLen----------------------------------



// I've finally decided to write a helper function
// I have just been finding it everytime I needed len 
std::size_t LinkedList::getLen() {
  Dugum*      gec {m_ilk};
  std::size_t len {0};
  while(gec) {
    ++len;
    gec = gec->sonra;
  }
  return len;
}



//-------------------------orderL----------------------------------



void LinkedList::orderL() {
  std::size_t len {getLen()};

  Dugum* gec {m_ilk};
  for(std::size_t i{0}; i < len; ++i) {

    for(std::size_t k{0}; k < i; ++k) gec = gec->sonra;

    Dugum* smallest {gec};
    for(std::size_t j{i}; j < len; ++j) {
      if(gec->matris.aritOrt() < smallest->matris.aritOrt()) {
        gec->matris.swap(smallest->matris);
        smallest = gec;
      }
      gec = gec->sonra;
    }
    
    gec = m_ilk;
  }
}



//-------------------------printD----------------------------------



// I called it list page it's just that the teacher wants us to print five
// at a time so each five would be a page. listPage = 1 till n
void LinkedList::printD(Screen& s, const std::size_t& listPage) {
  float listLen {static_cast<float>(getLen())};
  
  Dugum* gec {m_ilk};
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
      goToAd = "     0x0";
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



//-------------------------printMatris-----------------------------



void LinkedList::printMatris(Screen& s, const std::size_t& selectedD) {
  std::size_t listLen {getLen()};

  Dugum* gec {m_ilk};
  if(selectedD > listLen || selectedD == 0) throw std::out_of_range("Error printM(s, selectedD): selectedD is out of range.");

  for(std::size_t i{0}; i < (selectedD - 1); ++i) {
    gec = gec->sonra;
  }
  
  gec->matris.print(s, selectedD);
}



//-------------------------printMD---------------------------------



void LinkedList::printMD(Screen& s, const std::size_t listPage, const std::size_t& selectedD) {
  s.clear();

  // puts a separator at the start of the page
  s.save(1, 0, "--------------------------------------------------");

  // puts a separated at the end of the page
  s.save(43, 0, "--------------------------------------------------");

  printD     (s, listPage);
  printMatris(s, selectedD);
}



//-------------------------printMenu-------------------------------



void LinkedList::printMenu(Screen& s) {
  s.save(1, 60, "|---- Dugum gezilimi aktif -----------|");
  s.save(2, 60, "|    w/s tuslari ile gezebilirsiniz   |");
  s.save(3, 60, "|    q Tusu ile one dugum ekle        |");
  s.save(4, 60, "|    e Tusu ile arkaya dugum ekle     |");
  s.save(5, 60, "|    f Tusu ile dugum secilebilir     |");
  s.save(6, 60, "|    x Tusu ile programi kapat        |");
  s.save(7, 60, "|-------------------------------------|");
}



//-------------------------printAll--------------------------------



void LinkedList::printAll(Screen& s, std::size_t& listPage, std::size_t& selectedD, const char& usrInput, bool& isRunning) {
  std::size_t listLen {getLen()};
  static bool isMatris {false};

  // I could have made this as enum but I have already done it and I don't feel like changing it
  if(!isMatris) {
    switch(usrInput) {
    case 'w':
      if(selectedD > 1) --selectedD; // 1 is the first dugum
      break;

    case 's':
      if(selectedD < listLen) ++selectedD;
      break;

    case 'q':
      addLower(selectedD);
      break;

    case 'e':
      addUpper(selectedD);
      break;

    case 'f':
      isMatris = true;
      break;

    case 'x':
      isRunning = false;
      break;
    default: break;
    }
  }
  listPage = (selectedD - 1) / 5 + 1; // this would turn the page if needed
  if(!isMatris)
    orderL();
  printMD(s, listPage, selectedD);
  if(isMatris) {
    Dugum* gec {m_ilk};

    // we are checking the selectedD in the switch case so 
    // it should be fine to just use it without checking
    for(std::size_t i{1}; i < selectedD; ++i) gec = gec->sonra;

    bool isDeleteNode {false};
    gec->matris.printAll(s, selectedD, usrInput, isMatris, isDeleteNode);

    if(isDeleteNode) {
      if(!gec->sonra) {
        if(gec != m_ilk)
          --selectedD;
      }
      
      remove(gec);
    }
    printMD(s, listPage, selectedD);
    gec->matris.printMatrisM(s);
  }
  if(!isMatris) {
    s.clearMenu();
    printMenu(s);
  }
}