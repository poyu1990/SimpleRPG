#include "Item.h"

Item::Item()
{
    for (int i = 31; i >= 0; i--)
    {
        table[i] = 1<<i;
        count[i] = 0;
        have[i] = false;
    }
    
    name[31] = "Copper Sword";
    name[30] = "Iron Sword";
    name[29] = "Steel Sword";
    name[28] = "Lightsaber";
    name[27] = "Copper Crossbow";
    name[26] = "Iron Crossbow";
    name[25] = "Steel Crossbow";
    name[24] = "Bazooka";
    name[23] = "Leather Cap";
    name[22] = "Iron Hat";
    name[21] = "Steel Helmet";
    name[20] = "Hyneman Baret";
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
    name[8] = "Divine Water";
    name[7] = "Chuck Norris";
    name[6] = "";
    name[5] = "";
    name[4] = "";
    name[3] = "";
    name[2] = "";
    name[1] = "";
    name[0] = "";
    
    /*
     table[0] = 0x80000000;
     table[1] = 0x40000000;
     table[2] = 0x20000000;
     table[3] = 0x10000000;
     table[4] = 0x08000000;
     table[5] = 0x04000000;
     table[6] = 0x02000000;
     table[7] = 0x01000000;
     table[8] = 0x00800000;
     table[9] = 0x00400000;
    table[10] = 0x00200000;
    table[11] = 0x00100000;
    table[12] = 0x00080000;
    table[13] = 0x00040000;
    table[14] = 0x00020000;
    table[15] = 0x00010000;
    table[16] = 0x00008000;
    table[17] = 0x00004000;
    table[18] = 0x00002000;
    table[19] = 0x00001000;
    table[20] = 0x00000800;
    table[21] = 0x00000400;
    table[22] = 0x00000200;
    table[23] = 0x00000100;
    table[24] = 0x00000080;
    table[25] = 0x00000040;
    table[26] = 0x00000020;
    table[27] = 0x00000010;
    table[28] = 0x00000008;
    table[29] = 0x00000004;
    table[30] = 0x00000002;
    table[31] = 0x00000001;
*/

}

Item::~Item()
{             
}

int Item::lookup(long int x, int y)
{
    switch(y)
    {
        case 1:       for (int i = 31; i > 11; i--)
                          if (table[i] & x)
                             return i;
                      break;
        case 2:       for (int i = 11; i > 6; i--)
                          if (table[i] & x)
                             return i;
                      break;
    }
}

int Item::itemGain(int index, int amount)
{
    have[index] = true;
    count[index] += amount;
}


int Item::itemUse(int index)
{
    if(have[index])
		count[index] -= 1;

	if(count[index] == 0)
		have[index] = false;
}

void Item::inventory(string something[], int count2[])
{
    int i = 0;
    long int x = 0xffffffff;
    
    for (int j = 0; j < 32; j++)
        if (have[j])
        {
            something[i] = name[j];
            count2[i] = count[j];
            i++;
        }
}




