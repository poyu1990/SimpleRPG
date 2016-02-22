#include "Equip.h"

Equip::Equip()
{
    item[31] = new Stats(10,0,1,1,1); //"Copper Sword";
    item[30] = new Stats(20,0,1,1,1); //"Iron Sword";
    item[29] = new Stats(50,0,1,1,1); //"Steel Sword";
    item[28] = new Stats(999,999,999,999,999); //"Lightsaber";
    item[27] = new Stats(10,0,1,1,1); //"Copper Crossbow";
    item[26] = new Stats(20,0,1,1,1); //"Iron Crossbow";
    item[25] = new Stats(50,0,1,1,1); //"Steel Crossbow";
    item[24] = new Stats(999,999,999,999,999); //"Bazooka";
    item[23] = new Stats(0,10,1,1,1); //"Leather Cap";
    item[22] = new Stats(0,20,1,1,1); //"Iron Hat";
    item[21] = new Stats(0,50,1,1,1); //"Steel Helmet";
    item[20] = new Stats(999,999,999,999,999); //"Hyneman Baret";
    item[19] = new Stats(0,10,1,1,1); //"Leather Pelt";
    item[18] = new Stats(0,20,1,1,1); //"Copper Plate";
    item[17] = new Stats(0,50,1,1,1); //"Chainmail";
    item[16] = new Stats(999,999,999,999,999); //"Energy Shield";
    item[15] = new Stats(0,10,1,1,1); //"Cotton Pants";
    item[14] = new Stats(0,20,1,1,1); //"Kilts";
    item[13] = new Stats(0,50,1,1,1); //"Shin Guard";
    item[12] = new Stats(999,999,999,999,999); //"Diaper";
    item[11] = new Stats(); //"Potion";
    item[10] = new Stats(); //"Hi-Potion";
     item[9] = new Stats(); //"X-Potion";
     item[8] = new Stats(); //"Divine Water";
     item[7] = new Stats(); //"Chuck Norris";
     item[6] = new Stats(); //"";
     item[5] = new Stats(); //"";
     item[4] = new Stats(); //"";
     item[3] = new Stats(); //"";
     item[2] = new Stats(); //"";
     item[1] = new Stats(); //"";
     item[0] = new Stats(); //"";
     index = 0;
}

Equip::~Equip(){}

int getAtt()
{
    return item[index].att;
}

int getDef()
{
    return item[index].def;    
}

int getAcc()
{
    return item[index].acc;    
}

int getSkill()
{
    return item[index].skill;
}

int getRate()
{
    return item[index].rate;
}

int& getIndex()
{
    return index;
}
