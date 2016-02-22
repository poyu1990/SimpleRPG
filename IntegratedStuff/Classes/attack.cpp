
#include "attack.h"

attack::attack()
{
    for (int i = 31; i < 0; i--)
        table[i] = 1<<i;
    for (int i = 0; i < 32; i++)
    {
        //count[i] = 0;
        type[i] = 0;
        accMod[i] = 0;
        dmgMod[i] = 0;
        dmgType[i] = 0;
        rate[i] = 0;
    }
        // 1 = melee, 2 = ranged, 6 = will
    name[31] = "Bland Punch";
    type[31] = 1;
    accMod[31] = 1;
    dmgMod[31] = 4;
    dmgType[31] = 1;
    rate[31] = 2;
    name[30] = "Heavy Punch";
    type[30] = 1;
    accMod[30] = 0;
    dmgMod[30] = 10;
    dmgType[30] = 1;
    rate[30] = 1;
    name[29] = "Deathray";
    type[29] = 2;
    accMod[29] = 3;
    dmgMod[29] = 6;
    dmgType[29] = 6;
    rate[29] = 2;
     name[28] = "Roundhouse Kick";
    type[28] = 1;
    accMod[28] = 9;
    dmgMod[28] = 99;
    dmgType[28] = 1;
    rate[28] = 1;
    name[27] = "Copper Crossbow";
    name[26] = "Iron Crossbow";
    name[25] = "Steel Crossbow";
    name[24] = "Bazooka";
    name[23] = "Leather Cap";
    name[22] = "Iron Hat";
    name[21] = "Steel Helmet";
    name[20] = "Hyneman Beret";
    name[19] = "Leather Pelt";
    name[18] = "Copper Plate";
    name[17] = "Chainmail";
    name[16] = "Energy Shield";
    name[15] = "Cotton Pants";
    name[14] = "Kilts";
    name[13] = "Shin Guard";
    name[12] = "Diaper";
    name[11] = "Potion";
    name[10] = "Hi-Potion";
    name[9] = "X-Potion";
    name[8] = "Phoenix Down";
    name[7] = "Chuck Norris";
    name[6] = "";
    name[5] = "";
    name[4] = "";
    name[3] = "";
    name[2] = "";
    name[1] = "";
    name[0] = "";
    
}

attack::~attack()
{
                 }

const int attack::data(int which, int id)
{
                 switch(which)
                 {
                              case 1:
                                   return type[id];
                              case 2:
                                   return accMod[id];
                              case 3:
                                   return dmgMod[id];
                              case 4:
                                   return dmgType[id];
                              case 5:
                                   return rate[id];
                 }
}

const string attack::nameData(int id)
{
      return name[id];
}
