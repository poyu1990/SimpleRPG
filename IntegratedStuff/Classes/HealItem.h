#include <cstdlib>
#include <iostream>
#include "Item.h"

class HealItem : public Item
{
public:
	HealItem();
	~HealItem();
  
  int use(int i);
  int lookup(string s);     
  
  private:
  int amount[32];
  
};
