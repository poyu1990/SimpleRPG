#ifndef CHARACTER
#define CHARACTER
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string.h>
#include "Item.h"
#include "GraphicsInterface.h"

class Character
{
      public:
             
      Character(int hpIn = 100, int initIn = 1, int meleeIn = 1, int rngIn = 1, int athIn = 1, int defIn = 1, int willIn = 1, std::string nameIn = "?", GraphicsInterface* INgraphics = NULL, int xIn = 9999, int yIn = 0, std::string tile="player_down");
      ~Character();
      
      void damage(int amount);
      void useItem(long int item);
      void levelUp(int experience);
      bool alive();
      std::string status();
      void increaseHP(int amount);
      bool gainExp(int newExp);
      void equip(int index, int x);
      void unequip(int index);
      const int getInit();
      const int getAttr(int which);
      const std::string getName();
      void addAttk(int index, int atkNum);
      const int getAttk(int index);
      int atks[4];
      SpriteObject* pic;
      int x, y;
      GraphicsInterface* graphics;  
      void getCol(int& outX, int& outY);
      void setCol(int inX, int inY);
	Item* getItem();
      
      private:
      long int inventory;
      int equipd[4];
      std::string picName;
      std::string name;
      void incAtt(int i);
      void incDef(int i);
      //Equip hand, head,body,bottom;
      int hp, baseHP, exp, level, expToNextLevel, expBase, attackNum, 
      melee, rng, init, def, ath, money, will;
      //need sprite pointer
      Item invent;
      
      

};
#endif
