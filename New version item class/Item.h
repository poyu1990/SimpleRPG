#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Item
{
      public:
             
      Item();
      ~Item();
      
      static int lookup(long int x);
      static int itemGain(int index, int amount = 1);
      static void inventory(string something[] , int count2[]);
      static string returnName(int x);
      
      protected:
      long int table[32];
      string name[32];
      int count[32];
      bool have[32];
      enum ERR {WRONGITEM};
};
