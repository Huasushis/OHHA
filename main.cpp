#include "ohha.h"
#include<cstdio>
#include<iostream>
#include<ctime>
using namespace std;
string filepath;
#define ull unsigned long long
int main(){
  printf("Please input the file of which you want to get the hash\n");
  getline(cin,filepath);
  ull st=clock(),ed;
  ohha::SetFilename(filepath);
  cout<<ohha::GetHash();
  ed=clock();
  printf("\nTime Used:%.3lfs",(ed-st)*1.0/1000);
  return 0;
}