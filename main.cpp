#include "ohha.h"
#include<cstdio>
#include<iostream>
using namespace std;
string filepath;
int main(){
  printf("Please input the file of which you want to get the hash\n");
  getline(cin,filepath);
  ohha::SetFilename(filepath);
  cout<<ohha::GetHash();
  return 0;
}