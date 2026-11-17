#ifndef PRINT
#define PRINT
#include "Common.hpp"

constexpr std::size_t printableObjects {4}; // this is the amount of things that I can print
constexpr std::size_t x                {50};
constexpr std::size_t y                {7};

char output[printableObjects][y][x] {
  { // 1 Dugum gösterimi
    {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},

    {'*','*'}, // I somehow need to make this store the address of the node

    {'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},

    {'*','*'}, // this will hold the Matris aritmetik ortalama value

    {'_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},

    {'*','*'}, // this will hold the address that the node will go to so Dugum->sonra

    {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
  },
};


#endif