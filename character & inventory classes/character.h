#include <iostream>
#include <cstdlib>

class Character
{
      public:
             
      Character();
      ~Character();
      
      void damage(int amount);
      void useItem(long int item);
      void levelUp(int experience);
      void increaseHP(int amount);
      void getNewExp(int exp);
      void equip(long int item);
      void unequip(long int item);
      
      private:
      void incAtt();
      void incDef();
      Equip hand, head, body, bottom;
      int hp, baseHp, exp, level, expToNextLevel, expBase, att, def, money;
      //need sprite pointer
      //Item invent;
      
      

};
