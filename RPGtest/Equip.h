#include <iostream>
#include <cstdlib>
#include "Item.h"
using namespace std;

struct Stats
{
       int att, def, acc, skill, rate;
       
       Stats()
       {
              att = 0;
              def = 0;
              acc = 0;
              skill = 0;
              rate = 0;
       }
       
       Stats(int a,int d, int ac, int s, int r)
       {
           att = a;
           def = d;
           acc = ac;
           skill = s;
           rate = r;
       }
       
};

class Equip : public Item
{
      public:
      Equip();
      ~Equip();
      
      int getAtt();
      int getDef();
      int getAcc();
      int getSkill();
      int getRate();      
      int& getIndex();
      
      private:
      Stats item[32];
      int index;
      
};
