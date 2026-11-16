#ifndef MATRISDUGUM
#define MATRISDUGUM

class Matris;

class MatrisDugum {
public:
  MatrisDugum() = default;
  MatrisDugum(const int& ver) : m_ver{ver} {};

  void push(const int& ver) { m_ver = ver; }
  int get() { return m_ver; };

private:
  MatrisDugum* sonra {};
  MatrisDugum* once  {};
  int m_ver {};

  friend Matris;
};

#endif