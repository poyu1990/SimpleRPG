#include <iostream>
#include <cstdlib>
#include "Character.h"

using namespace std;

typedef void (Menu::*FUNC)(int);

class Menu
{
      public:
      Menu();
      ~Menu();
      
      void Stats(int x);
      void Inventory(int x);
      void save(int x);
      void quit(int x);
      
      
      
      private:
      string name[4];
      FUNC list[4];
};      
