#ifndef DUGUM
#define DUGUM
class Dugum {
public:
  Dugum() = default;
  Dugum(int matris) {
    this->matris = matris;
  }

  // this is just a place holder for the Matris class that I would have later
  using Matris = int;
  Matris matris{};
  
  Dugum* sonra{}; // for now I'm only gonna move forwards
};

#endif