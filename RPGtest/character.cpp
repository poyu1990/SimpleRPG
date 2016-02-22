#include "character.h"



Character::Character(int hpIn, int initIn, int meleeIn, int rngIn, int athIn, int defIn, int willIn, std::string nameIn)
{
  hp = hpIn;
  init = initIn;
  melee = meleeIn;
  rng = rngIn;
  ath = athIn;
  def = defIn;
  will = willIn;
  name = nameIn;
  exp = money = 0;
  level = 1;
  expToNextLevel = expBase = 10;
  for(int i =0; i<4; i++)
  equipd[i]=0;
  
  
}



Character::~Character()
{
}
const int Character::getInit()
{
      return init;
}
const int Character::getAttr(int which)
{
      switch(which)
      {
                   case 1:
                        return melee;
                   case 2:
                        return rng;
                   case 3:
                        return ath;
                   case 4:
                        return init;
                   case 5:
                        return hp;
                   case 6:
                        return will;
                   case 7:
                        return def;
      }      
}
const std::string Character::getName()
{
      return name;
}
void Character::damage(int amount)
{
     hp -= amount;
     if(hp < 0)hp=0;
}

void Character::useItem(long int item)
{
     //invent.use(item)
}

void Character::levelUp(int experience)
{
      expToNextLevel -= experience;
      if (expToNextLevel <= 0)
         level++;
      getNewExp(expToNextLevel);
      expToNextLevel = expBase + expToNextLevel;
         
}

bool Character::alive()
{
     if(hp > 0) return true;
     return false;
}

std::string Character::status()
{
       std::stringstream msg;
       msg<<name<<" HP: "<<hp;
       return msg.str();
}

void Character::increaseHP(int amount)
{
     hp += amount;
}

void Character::getNewExp(int exp)
{
    // baseExp *= 1.50;
}

void Character::incAtt(int i)
{
     //att += hand.att*1;    
}

void Character::incDef(int i)
{
    // def += item.def*i;
}

void Character::equip(int index, int x)
{
/*
     switch (x)
     {
            case 1:       hand.getIndex() = index; break;
            case 2;       head.getIndex() = index; break;
            case 3;       body.getIndex() = index; break;
            case 4;       bottom.getIndex() = index; break;
     }
     */
}

void Character::unequip(int index)
{
     /*
     switch (x)
     {
            case 1:       hand.getIndex() = 0; break;
            case 2;       head.getIndex() = 0; break;
            case 3;       body.getIndex() = 0; break;
            case 4;       bottom.getIndex() = 0; break;
     }
     */
}


