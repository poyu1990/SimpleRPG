#include "Equip.h"

Equip::Equip()
{
    item[31] = Stats(10,0,1,1,1); //"Copper Sword";
    item[30] = Stats(20,0,1,1,1); //"Iron Sword";
    item[29] = Stats(50,0,1,1,1); //"Steel Sword";
    item[28] = Stats(999,999,999,999,999); //"Lightsaber";
    item[27] = Stats(10,0,1,1,1); //"Copper Crossbow";
    item[26] = Stats(20,0,1,1,1); //"Iron Crossbow";
    item[25] = Stats(50,0,1,1,1); //"Steel Crossbow";
    item[24] = Stats(999,999,999,999,999); //"Bazooka";
    item[23] = Stats(0,10,1,1,1); //"Leather Cap";
    item[22] = Stats(0,20,1,1,1); //"Iron Hat";
    item[21] = Stats(0,50,1,1,1); //"Steel Helmet";
    item[20] = Stats(999,999,999,999,999); //"Hyneman Baret";
    item[19] = Stats(0,10,1,1,1); //"Leather Pelt";
    item[18] = Stats(0,20,1,1,1); //"Copper Plate";
    item[17] = Stats(0,50,1,1,1); //"Chainmail";
    item[16] = Stats(999,999,999,999,999); //"Energy Shield";
    item[15] = Stats(0,10,1,1,1); //"Cotton Pants";
    item[14] = Stats(0,20,1,1,1); //"Kilts";
    item[13] = Stats(0,50,1,1,1); //"Shin Guard";
    item[12] = Stats(999,999,999,999,999); //"Diaper";
    item[11] = Stats(); //"Potion";
    item[10] = Stats(); //"Hi-Potion";
     item[9] = Stats(); //"X-Potion";
     item[8] = Stats(); //"Divine Water";
     item[7] = Stats(); //"Chuck Norris";
     item[6] = Stats(); //"";
     item[5] = Stats(); //"";
     item[4] = Stats(); //"";
     item[3] = Stats(); //"";
     item[2] = Stats(); //"";
     item[1] = Stats(); //"";
     item[0] = Stats(); //"";
     index = 0;
}

Equip::~Equip(){}

int Equip::getAtt()
{
    return item[index].att;
}

int Equip::getDef()
{
    return item[index].def;    
}

int Equip::getAcc()
{
    return item[index].acc;    
}

int Equip::getSkill()
{
    return item[index].skill;
}

int Equip::getRate()
{
    return item[index].rate;
}

int& Equip::getIndex()
{
    return index;
}
