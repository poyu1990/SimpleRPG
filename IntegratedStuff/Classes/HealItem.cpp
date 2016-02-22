#include "HealItem.h"

HealItem::HealItem()
{
    amount[11] = 50;
    amount[10] = 100;
    amount[9] = 200;
    amount[8] = 300;
    amount[7] = 99999;
}
HealItem::~HealItem()
{
}

int HealItem::use(int i)
{
    if (i >12 || i < 6)
		throw WRONGITEM;
    else 
		return amount[i];
}

int HealItem::lookup(string s)
{
    for (int i = 7; i < 12; i++)
        if (s == name[i])
			return i;
}
