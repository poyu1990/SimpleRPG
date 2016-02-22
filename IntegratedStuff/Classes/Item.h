#ifndef ITEM
#define ITEM
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Item
{
      public:
             
      Item();
      ~Item();
      
      int lookup(long int x, int x);
	  int itemGain(int index, int amount = 1);
	  int itemUse(int index);
      void inventory(string something[] , int count2[]);
      
      
      protected:
	bool have[32];

  	long int table[32];
      string name[32];
      int count[32];
      enum ERR {WRONGITEM};
};

#endif
