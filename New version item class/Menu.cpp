Menu()
{
      list[0] = &Menu::stats;
      list[1] = &Menu::inventory;
      list[2] = &Menu::save;
      list[3] = &Menu::quit;

      
}
~Menu()
{
       delete list;       
}

void stats(long int x)
{
     // call graphics to print equip and stats e.g.  hand: lightsaber etc.     
}
void inventory(long int x)
{
     string itemList[32];
     int count[32];
     Item::inventory(itemList, count);
     //call graphics to print the arrays    
}
void save(long int x)
{
     //call someone else's save
}
void quit(long int x)
{
     //call graphical quit     
}
