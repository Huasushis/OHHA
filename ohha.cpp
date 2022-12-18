#include "ohha.h"
#include <cstring>
#define f(i, j, k) for (int i = j; i < k; ++i)
using namespace std;

namespace ohha
{
  // MT19937
  bool isInit;
  int index;
  unsigned int MT[624];
  void srand(int seed)
  {
    index = 0;
    isInit = 1;
    MT[0] = seed;
    for (int i = 1; i < 624; i++)
    {
      unsigned int t = 1812433253 * (MT[i - 1] ^ (MT[i - 1] >> 30)) + i;
      MT[i] = t & 0xffffffff;
    }
  }

  void generate()
  {
    for (int i = 0; i < 624; i++)
    {
      unsigned int y = (MT[i] & 0x80000000) + (MT[(i + 1) % 624] & 0x7fffffff);
      MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
      if (y & 1)
        MT[i] ^= 2567483615;
    }
  }

  unsigned int Rand()
  {
    if (index == 0)
      generate();
    unsigned int y = MT[index];
    y = y ^ (y >> 11);
    y = y ^ ((y << 7) & 2636928640);
    y = y ^ ((y << 15) & 4022730752);
    y = y ^ (y >> 18);
    index = (index + 1) % 624;
    return y;
  }
  unsigned long long length;
  ifstream fin;
  TernaryNumber OriginalNum;
  TernaryNumber son[10];
  bool haveadded;
  TernaryNumber::TernaryNumber() // init
  {
    f(i, 0, 162)
    {
      num[i] = 0;
    }
  }
  short &TernaryNumber::operator[](int i)
  {
    return num[i];
  }
  TernaryNumber &TernaryNumber::operator=(string n)
  {
    f(i, 0, 162)
    {
      this->num[i] = n[i];
    }
    return *this;
  }
  bool TernaryNumber::iszero()
  {
    f(i, 0, 162)
    {
      if (num[i])
        return 0;
    }
    return 1;
  }

  void SetFilename(string filename) // Change/Set a file
  {
    fin.open(filename, ios::in | ios::binary);
    length = 0;
    if (!fin)
    {
      throw "File Not Found";
    }
    OriginalNum = string("112202210022010020102221122112212010212101020020200102222002012210110201001100021100002000200102100010101112221020121100200022102201002101011220120101211211002222");
    haveadded = 0;
  }
  string GetHash() // GetHash
  {
    if (!fin)
    {
      throw "Please Set File First!";
    }
    short s[70];
    short byte, pointer = 0;
    TernaryNumber adder;
    while (fin.read((char *)&byte, sizeof(char))) // Read the file
    {
      length += 8;
      s[pointer++] = (byte >> 4);
      s[pointer++] = (byte % 16);
      if (pointer == 64)
      {
        adder = TwoToThree(s); // To the ternary number
        addnum(adder);         // Add the ternary number
        pointer = 0;
      }
    }
    s[pointer++] = 8;
    s[pointer++] = 0;
    while (pointer != 48)
    {
      if (pointer == 64)
      {
        adder = TwoToThree(s); // To the ternary number
        addnum(adder);         // Add the ternary number
        pointer = 0;
      }
      s[pointer++] = 0;
      s[pointer++] = 0;
    }
    for (int i = 60; i >= 0; i -= 4)
    {
      s[pointer++] = (length >> i) % 16ull;
    }
    adder = TwoToThree(s);
    addnum(adder);
    pointer = 0;
    return ThreeToTwo(OriginalNum);
  }
  TernaryNumber TwoToThree(short *num)
  {
    TernaryNumber ans;
    short quot[64]; // quotient
    memset(quot, 0, sizeof quot);
    short pointer = 161, rest = 0;
    while (!iszero(num) && pointer >= 0)
    { // division
      rest = 0;
      f(i, 0, 64)
      {
        quot[i] = (num[i] + (rest << 4)) / 3;
        rest = (num[i] + (rest << 4)) % 3;
      }
      ans[pointer--] = rest;
      f(i, 0, 64) num[i] = quot[i];
    }
    return ans;
  }
  bool iszero(short *num)
  {
    f(i, 0, 64)
    {
      if (num[i])
        return 0;
    }
    return 1;
  }
  void addnum(TernaryNumber num)
  {
    if (!haveadded)
    {
      haveadded = 1;
      int tmp = 0; // GetSeed
      f(i, 0, 162)
      {
        tmp += OriginalNum[i] * num[i];
      }
      srand(tmp);
    }
    short x, y;
    f(i, 0, 10)
    {
      f(j, 0, 162)
      {
        son[i][j] = combine(GetGene(OriginalNum[j]), GetGene(num[j]));
      }
    }
    short maxn, v;
    f(i, 0, 10)
    {
      x = y = 0;
      f(j, 0, 162)
      {
        if ((OriginalNum[j] + 1) % 3 == son[i][j])
          ++x;
        else if ((son[i][j] + 1) % 3 == OriginalNum[j])
          ++y;
      }
      if (i == 0)
      {
        maxn = y - x;
        v = 0;
      }
      else if (y - x > maxn)
      {
        maxn = y - x;
        v = i;
      }
    }
    f(j, 0, 162) OriginalNum[j] = son[v][j];
  }
  short GetGene(short type)
  {
    short ans;
    if (type < 2)
      ans = type;
    else
      ans = rand() % 2;
    if (rand() % 100 == 0)
      return 1 - ans;
    return ans;
  }
  short combine(short fa, short ma)
  {
    if (fa == ma)
      return ma;
    return 2;
  }
  string ThreeToTwo(TernaryNumber num)
  {
    short ans[64];
    TernaryNumber quot; // quotient
    memset(ans, 0, sizeof(ans));
    short pointer = 63, rest = 0;
    while (!num.iszero() && pointer >= 0)
    { // division
      rest = 0;
      f(i, 0, 162)
      {
        quot[i] = (num[i] + (rest * 3)) / 16;
        rest = (num[i] + (rest * 3)) % 16;
      }
      ans[pointer--] = rest;
      f(i, 0, 162) num[i] = quot[i];
    }
    string sans;
    f(i, 0, 64)
    {
      sans.push_back(base[ans[i]]);
    }
    return sans;
  }
};