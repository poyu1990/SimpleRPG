#ifndef ATTACK
#define ATTACK
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class attack
{
      public:
             
      attack();
      ~attack();
      const int data(int which, int id);
      const string nameData(int id);
      
      private:
      long int table[32];
      string name[32];
      int type[32];
      int accMod[32];
      int dmgType[32];
      int dmgMod[32];
      int rate[32];
};
#endif
