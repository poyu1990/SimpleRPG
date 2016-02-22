#ifndef CHARACTER
#define CHARACTER
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include "Item.h"

class Character
{
      public:
             
      Character(int hpIn = 100, int initIn = 1, int meleeIn = 1, int rngIn = 1, int athIn = 1, int defIn = 1, int willIn = 1, std::string nameIn = "?");
      ~Character();
      
      void damage(int amount);
      void useItem(long int item);
      void levelUp(int experience);
      bool alive();
      std::string status();
      void increaseHP(int amount);
      void getNewExp(int exp);
      void equip(int index, int x);
      void unequip(int index);
      const int getInit();
      const int getAttr(int which);
      const std::string getName();
      
      
      private:
      long int inventory;
      int equipd[4];
      std::string name;
      void incAtt(int i);
      void incDef(int i);
      //Equip hand, head,body,bottom;
      int hp, baseHP, exp, level, expToNextLevel, expBase, attackNum, 
      melee, rng, init, def, ath, money, will;
      //need sprite pointer
      //Item invent;
      
      

};
#endif
