#include <iostream>
#include <cstdlib>

using namespace std;

class Item
{
      public:
             
      Item();
      ~Item();
      void lookUp(String s[]);
      void count(int a[]);
      
      
      protected:
      long int table[32];
      string* name[32];
      int count[32];
};
