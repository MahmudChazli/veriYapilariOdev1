#ifndef MATRISDUGUM
#define MATRISDUGUM

class MatrisDugum {
public:
  MatrisDugum() = default;
  void push(const int& ver) { m_ver = ver; }
  int get() { return m_ver; };

private:
  int m_ver {};
  MatrisDugum* next {};
};

#endif