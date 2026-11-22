/**
* @file Matris.cpp
* @description Bağlı listede her düğüm, 1 ile 100 arası sayılardan olusur ve her terimleri essiz bir kare matris tutar. 
*              Matriste satır ve sütun silme, yer değiştirme ve aritmetik ortalama işlemleri yapılır.
* @course veri yapilari
* @assignment 1.odev
* @date 22.10.2060
* @author Mahmud chazli mahmud.chazli@ogr.sakarya.edu.tr
*/

#include "../include/Common.hpp"
#include "../include/Matris.hpp"
#include <windows.h>
#include <cctype>



//--------------------------------delete---------------------------------------------



// column = 1 den height kadar gider
void Matris::deleteColumn(const std::size_t& column) {
  if(column <= 0 || column > m_width) throw std::out_of_range("Boyle bir sutun yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris should be deleted.
  assert(m_width > 1 && "the caller didn't delete the dugum before deleteColumn() was called");
  
  std::size_t deleteIndex {column - 1};

  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}; i < m_len; ++i) {

    // I thought this would be harder than just this
    if(i % m_width == deleteIndex) {
      MatrisDugum* sil {};
      if(i == 0) {
        sil = m_ilk;
        m_ilk = m_ilk->sonra;
        m_ilk->once = nullptr;
        gec = m_ilk;

      }else {
        sil = gec;
        MatrisDugum* sonra {gec->sonra};
        MatrisDugum* once  {gec->once};
        once->sonra = sonra;
        if(sonra) sonra->once = once;
        gec = sonra;
      }
      delete sil;
    }else {
      gec = gec->sonra;
    }
  }
  m_len -= m_height;
  --m_width; // we change the width since we deleted a column
}

// row = 1 den width kadar gider
void Matris::deleteRow(const int& row) {
  if(row <= 0 || row > m_height) throw std::out_of_range("Boyle bir satir yok.");


  // this check shouldn't be here rather it should be in
  // the place that the function is being called at.
  // this means that this is the last thing on the matris and the matris should be deleted.
  assert(m_height > 1 && "the caller didn't delete the dugum before deleteRow() was called");

  int deleteIndex {(row - 1) * (int)m_width}; 

  MatrisDugum* gec {m_ilk};
  for(int i{0}; i < m_len; ++i) {
    
    if(i >= deleteIndex && i < (deleteIndex + m_width)) {
      MatrisDugum* sil {gec};

      if(deleteIndex == 0) {
        gec = gec->sonra;
        m_ilk = gec;
        m_ilk->once = nullptr;

      }else {      
        gec->once->sonra = gec->sonra;
        if(gec->sonra) gec->sonra->once = gec->once;
        gec = gec->sonra;
      }
      delete sil;  
    }else {
      gec = gec->sonra;
    }
  }
  m_len -= m_width;
  --m_height; // we change the height since we deleted a row
}



//-------------------------------satirSutunDeg---------------------------------------------



void Matris::satirSutunDeg(Screen& s, bool& isMatris) {

  if(m_width == m_height) {

    std::size_t usrInput  {};
    std::size_t sutunSwap {};
    int satirSwap {};

    bool isInput {false};
    while(!isInput) {
      s.clearMenu();
      printRCDegM(s);

      std::cout << "\033[2J\033[1;1H";

      s.print();

      std::cin >> usrInput;

      // flush the intput stream if it has an error
      if(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        MessageBoxW(
          NULL, 
          L"Verilen aralik arasinda secmelisiniz",
          L"Error!",
          MB_ICONEXCLAMATION | MB_OK
        );
        
        continue;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      if(usrInput == 0) {
        isMatris = false;
        break;
      }


      if(usrInput <= m_height) {
        satirSwap = sutunSwap = usrInput;
        isInput = true;

      }else {
        MessageBoxW(
          NULL, 
          L"Verilen aralik arasinda secmelisiniz",
          L"Error!",
          MB_ICONEXCLAMATION | MB_OK
        );
      }
    }

    if(satirSwap) {
      std::size_t satirI {(satirSwap - 1) * m_width}; // Satir Index
      std::size_t sutunI {sutunSwap - 1}; // Sutun Index

      int* satir {new int[m_width]};
      int* sutun {new int[m_height]};

      MatrisDugum* gec {m_ilk};

      // this brings the gec to where satir starts
      for(std::size_t i{0}; i < satirI; ++i) gec = gec->sonra;

      for(std::size_t i{satirI}; i < (satirI + m_width); ++i) {
        satir[i % m_width] = gec->get();
        gec = gec->sonra;
      }
      gec = m_ilk;

      for(std::size_t i{0}, sI{0}; i < m_len; ++i) {

        if(i % m_width == sutunI) {
          sutun[sI] = gec->get();
          gec->push(satir[sI]);

          ++sI;
        }

        gec = gec->sonra;
      }

      gec = m_ilk;
      // this brings the gec to where satir starts
      for(std::size_t i{0}; i < satirI; ++i) gec = gec->sonra;

      for(std::size_t i{satirI}; i < (satirI + m_width); ++i) {
        gec->push(sutun[i % m_width]);
        gec = gec->sonra;
      }
      delete[] satir;
      delete[] sutun;
    }

  }else {
    MessageBoxW(
      NULL, 
      L"Kare Matris Olmayan Bir Matris Satir Sutun Degistirilemez",
      L"Error!",
      MB_ICONEXCLAMATION | MB_OK
    );
  }
}



//-------------------------------aritOrt---------------------------------------------



double Matris::aritOrt() const {
  MatrisDugum* gec {m_ilk};
  double sum {0};
  while(gec) {
    sum += gec->get();
    gec = gec->sonra;
  }
  return ( sum / m_len );
}



//--------------------------------push-----------------------------------------------



void Matris::push(const int& veri) {
  if(!m_ilk) {
    m_ilk = new MatrisDugum(veri);
  }else {
    MatrisDugum* gec {m_ilk};
    while(gec->sonra) {
      gec = gec->sonra;
    }
    gec->sonra = new MatrisDugum(veri);
    gec->sonra->once = gec;
  }
}



//-------------------------printMatrisM---------------------------



void Matris::printMatrisM(Screen& s) {
  s.save(1, 60, "|---- Dugum islemleri aktif ----------|");
  s.save(2, 60, "|   1 Tusu ile Satir silin            |");
  s.save(3, 60, "|   2 Tusu ile Sutun silin            |");
  s.save(4, 60, "|   3 Tusu ile Satir sutun degistirin |");
  s.save(5, 60, "|   x Tusu ile dugum gezimine gidin   |");
  s.save(6, 60, "|-------------------------------------|");
}



//-------------------------printDeleteRM---------------------------



void Matris::printDeleteRM(Screen& s) {
  s.save(1, 60, "|---- Satir Silme Aktif -------------|");
  s.save(2, 60, "|   w/s Tuslari ile gezebilirisiniz  |");
  s.save(3, 60, "|   d Tusu ile secili satir silin    |");
  s.save(4, 60, "|   x Tusu ile dugum gezimine gidin  |");
  s.save(5, 60, "|------------------------------------|");
}



//-------------------------printDeleteCM----------------------------



void Matris::printDeleteCM(Screen& s) {
  s.save(1, 60, "|---- Sutun Silme Aktif -------------|");
  s.save(2, 60, "|   a/d Tuslari ile gezebilirisiniz  |");
  s.save(3, 60, "|   f Tusu ile secili satir silin    |");
  s.save(4, 60, "|   x Tusu ile dugum gezimine gidin  |");
  s.save(5, 60, "|------------------------------------|");
}




//-------------------------printRCDegM------------------------------



void Matris::printRCDegM(Screen& s) {

  s.save(1, 60, "|---- Satir Sutun Degisitir Aktif ---|");

  s.save(3, 60, "|   0 Tusu ile dugum gezimini gidin  |");
  s.save(4, 60, "|------------------------------------|");

  std::string save   {"|  1 - "};
  std::string widthS {std::to_string(m_width)};
  save += widthS + " arasi Satir/Sutun sec";
  s.save(2, 60, save);
  s.save(2, 97, "|");
}



//-------------------------printDeleteC----------------------------



bool Matris::printDeleteC(Screen& s, const std::size_t& selectedD, bool& isMatris) {
  s.clearMenu();
  printDeleteCM(s);

  std::size_t times      {0};
  std::size_t paddingRow {2};
  std::size_t paddingCol {30};
  std::size_t topR {((selectedD - 1) % 5) * 8 + paddingRow};

  // deletes the current matris variables
  for(std::size_t i{0}; i <= m_height; ++i) {
    for(std::size_t j{30}, width{0}; width < m_width; j += 3, ++width) {
      s.save(topR + i, j, "  ");
    }
  }

  char usrInput {};

  bool isRunning {true};
  while(isRunning) {

    std::size_t selectedC {paddingCol + times * 3};

    MatrisDugum* gec {m_ilk};
    for(std::size_t i{0}; i < m_height; ++i) {

      for(std::size_t j {paddingCol}, width{0}; width < m_width; j += 3, ++width) {
        s.save(topR + i + 1, j, std::to_string(gec->get()));
        gec = gec->sonra;
        
      }
    }
    

    s.save(topR, selectedC, "--");
    s.save(topR + m_height + 1, selectedC, "--");

    for(std::size_t i{0}; i <= m_height + 1; ++i) {
      for(std::size_t j {paddingCol - 1}, width{0}; width <= m_width; j += 3, ++width) {
        if(j == selectedC - 1 || j == selectedC + 2)
          s.save(topR + i, j, "|");
      }
    }


    std::cout << "\033[2J\033[1;1H";

    s.print();
    

    std::cin >> usrInput;

    if(std::cin.fail()) {
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(usrInput == 'x') {
      isMatris = false;
      return false;
    }

    // deletes the current matris variables
    for(std::size_t i{0}; i <= m_height + 1; ++i) {
      for(std::size_t j{paddingCol - 1}, width{0}; width <= m_width; j += 3, ++width) {
        s.save(topR + i, j, "     ");
      }
    }

    s.save(topR, paddingCol, " ");
    switch(usrInput) {
    case 'a':
      if(times > 0) --times;
      break;

    case 'd':
      if(times < m_width) ++times;
      break;

    case 'f':
      if(m_width == 1) {
        isMatris = false;
        return true; // we would need to delete the node
      }

      if(times == m_width) times + 1;

      deleteColumn(times + 1);
      
      if(times >= m_width) times = m_width - 1;
      break;

    default: break;
    }
  }

  return false;
}



//-------------------------printDeleteR----------------------------



bool Matris::printDeleteR(Screen& s, const std::size_t& selectedD, bool& isMatris) {
  s.clearMenu();
  printDeleteRM(s);

  std::size_t times      {0};
  std::size_t paddingRow {3};
  std::size_t paddingCol {28};
  std::size_t topR {((selectedD - 1) % 5) * 8 + paddingRow};

  // deletes the current matris variables
  for(std::size_t i{0}; i < m_height; ++i) {
    for(std::size_t j{30}, width{0}; width < m_width; j += 3, ++width) {
      s.save(topR + i, j, "  ");
    }
  }

  char usrInput {};

  bool isRunning {true};
  while(isRunning) {
    std::size_t row {topR + times + 1};

    for(std::size_t j{paddingCol}, width{0}; width < m_width; j += 3, ++width) {
      s.save(row - 1, j, "****");
      s.save(row + 1, j, "****");
    }

    s.save(row, paddingCol, "*");

    MatrisDugum* gec {m_ilk};
    for(std::size_t i{0}; i < m_height; ++i) {
      std::size_t line {topR + i};
      if(i >= times) ++line;
      if(i >  times) ++line;
      
      for(std::size_t j {paddingCol + 2}, width{0}; width < m_width; j += 3, ++width) {
        
        s.save(line, j, std::to_string(gec->get()));
        gec = gec->sonra;
      }
    }

    std::cout << "\033[2J\033[1;1H";

    s.print();
    
    std::cin >> usrInput;

    if(std::cin.fail()) {
      std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(usrInput == 'x') {
      isMatris = false;
      return false;
    }

    // deletes the current matris variables
    for(std::size_t i{0}; i <= m_height + 1; ++i) {
      for(std::size_t j{paddingCol}, width{0}; width <= m_width; j += 3, ++width) {
        s.save(topR + i, j, "    ");
      }
    }

    s.save(row, paddingCol, " ");
    switch(usrInput) {
    case 'w':
      if(times > 0) --times;
      break;

    case 's':
      if(times < m_height - 1) ++times;
      break;

    case 'd':
      if(m_height == 1) {
        isMatris = false;
        return true; // we would need to delete the node
      }

      if(times == m_height - 1) times + 1;

      deleteRow(times + 1);
      
      if(times >= m_height) times = m_height - 1;
      break;

    default: break;
    }
  }

  return false;
}



//-------------------------print-----------------------------------



// selected dugum is around 1 to 5
void Matris::print(Screen& s, const std::size_t& selectedD) {

  std::size_t paddingRow {3};
  std::size_t paddingCol {22};
  // times eight is just the dugum that it would be on
  std::size_t row {((selectedD - 1) % 5) * 8 + paddingRow};

  // this prints the arrows that show which dugum it currently has selected
  s.save(row,     paddingCol, "<-");
  s.save(row + 1, paddingCol, "<-");
  s.save(row + 2, paddingCol, "<-");
  s.save(row + 3, paddingCol, "<-");
  s.save(row + 4, paddingCol, "<-");
  s.save(row + 5, paddingCol, "<-");
  s.save(row + 6, paddingCol, "<-");

  paddingCol = 30;
  MatrisDugum* gec {m_ilk};
  for(std::size_t i{0}; i < m_height; ++i) {

    for(std::size_t j {paddingCol}, width{0}; width < m_width; j += 3, ++width) {

      s.save(row + i, j, std::to_string(gec->get()));

      gec = gec->sonra;
    }
  }
}



//-------------------------printAll--------------------------------



void Matris::printAll(Screen& s, const std::size_t& selectedD, const char& usrInput, bool& isMatris, bool& isDeleteNode) {
  enum class State { Menu, SatirS, SutunS, SSDeg };
  static State state {State::Menu};

  // the teacher had it that x would always bring them back to dugum gezim
  if(usrInput == 'x') {
    isMatris = false;
    state = State::Menu;
  }

  switch(state) {
  case State::Menu:
    switch(usrInput) {
    case '1': state = State::SatirS;
      break;
    case '2': state = State::SutunS;
      break;
    case '3': state = State::SSDeg;
      break;
    default: break;
    }
    break;

  case State::SatirS:
  case State::SutunS:
  case State::SSDeg:
  default:
    break;
  }
  
  switch(state) {
  case State::Menu:
    printMatrisM(s);
    break;

  case State::SatirS:
    isDeleteNode = printDeleteR(s, selectedD, isMatris);
    break;
  
  case State::SutunS:
    isDeleteNode = printDeleteC(s, selectedD, isMatris);
    break;

  case State::SSDeg:
    satirSutunDeg(s, isMatris);
    break;
  }

  state = State::Menu;
}



//--------------------------------swap-----------------------------------------------



void Matris::swap(Matris& m) {
  MatrisDugum* gec {m_ilk};
  std::size_t gecH {m_height};
  std::size_t gecW {m_width};
  std::size_t gecL {m_len};

  m_height = m.getH();
  m_width  = m.getW();
  m_len    = m.getL();
  m_ilk    = m.getIlk();

  m.setIlk(gec);
  m.setH(gecH);
  m.setW(gecW);
  m.setL(gecL);
}



//--------------------------------generate-------------------------------------------



void Matris::generate() {
  m_ilk->push(Random::get(0, 99));

  // we already have the first variable in the list so we start at 1 for newLen
  std::size_t newLen {1};
  for(std::size_t i{0}; i < m_len; ++i) { // this is a timer (the teacher has different sizes of matris)

    // this would get us a number between 0 and 100 inclusive
    int num = Random::get(0, 99);

    MatrisDugum* gec{m_ilk};
    for(std::size_t j{0}; j < newLen; ++j) {
      if(num == gec->get()) break;
      if(j == newLen - 1) {
        gec->sonra = new MatrisDugum(num);
        gec->sonra->once = gec;
        ++newLen;
      }
      gec = gec->sonra;
    }
    gec = m_ilk;
  }
  m_height = m_width = static_cast<std::size_t>(std::floor(sqrt(newLen)));

  // we would delete the extra variables and make a kare matris
  MatrisDugum* gec {m_ilk};
  while(gec->sonra) {
    gec = gec->sonra;
  }
  for(std::size_t i{newLen}; i > m_height * m_width; --i) {
    MatrisDugum* sil {gec};
    gec = gec->once;
    gec->sonra = nullptr;
    delete sil;
  }
  m_len = m_height * m_width;
  
  // the teacher wanted an error case for this for some reason
  switch(m_len) {
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