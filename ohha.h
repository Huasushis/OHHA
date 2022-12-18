#ifndef OHHA_H
#define OHHA_H

#include <string>
#include <fstream>

namespace ohha
{
  // MT19937
  extern bool isInit;
  extern int index;
  extern unsigned int MT[624];
  void srand(int seed);
  void generate();
  unsigned int Rand();

  class TernaryNumber
  {
  public:
    short num[162];
    TernaryNumber();
    short &operator[](int i);
    TernaryNumber &operator=(std::string n);
    bool iszero();
  };
  extern unsigned long long length;
  extern std::ifstream fin;
  extern TernaryNumber OriginalNum;
  extern TernaryNumber son[10];
  extern bool haveadded;
  static const char base[17] = "0123456789ABCDEF";
  void SetFilename(std::string filename);
  std::string GetHash();
  void addnum(TernaryNumber num);
  // base conversion
  TernaryNumber TwoToThree(short *num);
  std::string ThreeToTwo(TernaryNumber num);
  bool iszero(short *num);

  short GetGene(short type);
  short combine(short fa, short ma);
};
#endif