#include "character.h"



Character::Character(int hpIn, int initIn, int meleeIn, int rngIn, int athIn, int defIn, int willIn, std::string nameIn, GraphicsInterface* INgraphics, int xIn, int yIn, std::string tile)
{
  pic = NULL;
  hp = hpIn;
  baseHP = hpIn;
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
  graphics = INgraphics;
  for(int i =0; i<4; i++)
  {
  equipd[i]=0;
  atks[i]=0;
  }
  if(graphics != NULL && xIn != 9999)
  {
  pic = graphics->newSpriteObject(tile);
	x = xIn;
	y = yIn;
	pic->changePosition(x,y, -0.5, 0, 1.0f,0.0f);
 }
	
	invent.itemGain(11,3);
	
}

void Character::setCol(int inX, int inY)
{
     x = inX;
     y = inY;
     pic->changePosition(x,y, -0.5, 0, 1.0f,0.0f);
}
Character::~Character()
{
	if(pic)
	    delete pic;
}

void Character::addAttk(int index, int atkNum)
{
     if((index > -1) && (index < 4))
     atks[index] = atkNum;
     
}

const int Character::getAttk(int index)
{
      if((index > -1) && (index < 4))
      return atks[index];
      else return 0;
}

void Character::getCol(int& outX, int& outY)
{
      outX = x;
      outY = y;
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
                   case 8:
                        return baseHP;
                   case 9:
                        return exp;
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
     if(hp>baseHP) hp = baseHP;
}

bool Character::gainExp(int newExp)
{
     exp+=newExp;
     if(exp >= 100)
     {
		        exp -= 100;
                melee++;
                rng++;
                def++;
			    will++;
                baseHP+= 25;
                hp += 25;
		 return 1;
     }
                
	return 0;
    // baseExp *= 1.50;
}

Item* Character::getItem(){
	return &invent;
	
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


