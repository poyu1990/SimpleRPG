#include "battle.h"

Battle::Battle()
{
}

Battle::~Battle()
{
}


void Battle::run(Character you, Character them, int num = 1)
{
     
     // Your stats (will be passed via character class)
     //int hp = 100, defense = 5, melee = 5, init = 3;
     // Your attack(s) (will also be passed via character class)
     int type = 1, accBonus = 1, rate = 2, damage = 35;
     
     //Enemy stats (ditto)
     //int ehp = 150, edefense = 2, emelee = 2, eranged=5, einit = 7;
     int etype = 2, eaccBonus = 1, erate = 1, edamage = 35;
     
     //Number of combatants
     int combatants = 1 + num;
     initList initBattle[combatants], temp, temp2;
     // Insert while loop to do init
     do
     {
         initBattle[0].init = diceRoll(you.getInit());
         initBattle[0].person = you;
         initBattle[0].id = 1;
         initBattle[1].init = diceRoll(them.getInit());
         initBattle[1].person = them;
         initBattle[1].id = 2;
    
     } while(initBattle[0].init == initBattle[1].init);
     for(int r = 0; r < combatants-1; r++)
     {
				if(initBattle[r].init <initBattle[r+1].init )
				{
					temp=initBattle[r];
					temp2=initBattle[r+1];
					initBattle[r]=temp2;
					initBattle[r+1]=temp;
				}
     }
     
     while((you.alive()) && (them.alive()))
     {
               for(int t = 0; t < combatants; t++)
               {
                       int curRate = 6, rateUse = 0;
                           cout<<initBattle[t].person.getName()<<" is up!"<<endl;
                           cout<<initBattle[t].person.getName()<<" attacked!"<<endl;
                           
                           while((initBattle[t].id == 1)&&curRate > 0)
                           {
                           
                                        rateUse = attackTarget(initBattle[t].person, them, 30);  
                                        switch(rateUse)
                                        {
                                                       case 1:
                                                            rateUse += 3;
                                                       case 2:
                                                            rateUse += 1;
                                                       case 3:
                                                            rateUse += 2;  
                                        }
                                        curRate -= rateUse;   
                           }
                           while((initBattle[t].id == 2)&&curRate > 0)
                           {
                                         rateUse = attackTarget(initBattle[t].person, you, 29);  
                                        switch(rateUse)
                                        {
                                                       case 1:
                                                            rateUse += 3;
                                                       case 2:
                                                            rateUse += 1;
                                                       case 3:
                                                            rateUse += 2;  
                                        }
                                        curRate -= rateUse;   
                           }
               }
               cout<<"New round! "<<you.status()<<" and "<<them.status()<<endl;
               //system("PAUSE");
     }
     
     cout<<"The battle is over!"<<endl;
     if(!you.alive()) cout<<you.getName()<<" lost!"<<endl;
     else cout<<you.getName()<<" won!"<<endl;
                       
     
     
}

int Battle::attackTarget(Character attacker, Character &target, int attkNum)
{
     if(attackRoll((atkL.data(2, attkNum) + attacker.getAttr(atkL.data(1, attkNum))), target.getAttr(7)))
                                               {
                                                   cout<<attacker.getName()<<" hit with "<<atkL.nameData(attkNum)<<" for "
                                                   <<atkL.data(3, attkNum)*(attacker.getAttr(atkL.data(4, attkNum)))<<" damage!"<<endl;
                                                   target.damage(atkL.data(3, attkNum)*(attacker.getAttr(atkL.data(4, attkNum))));
                                                   
                                                   
                                               }
                                               else
                                               {
                                                   cout<<attacker.getName()<<" missed with "<<atkL.nameData(attkNum)<<"!"<<endl;
                                               }
                                               return atkL.data(5, attkNum);
     
}


bool Battle::attackRoll(int attack, int defense)
{
        attack = diceRoll(attack);
        defense = diceRoll(defense);
        if(defense > attack) return false;
        return true;
}

int Battle::diceRoll(int number)
{
    int success = 0, maxtimes = number, times = 1, next = 0, botch = 0;
string outstring;
int testroll[maxtimes];
  while (times <= maxtimes) { 
    testroll[times] = (rand()%10)+1;
    times++;
  }
  times = 1;
  while (times <= maxtimes) { 
    next = testroll[times];
    if ((next > 6)&&(next < 10)) { 
      success = success + 1;
    }
    else if (next < 2) { 
      botch = botch + 1;
    }
    else if (next > 9) { 
      success = success + 2;
    }
    times++;
  }
  if (success > 0)
  {
  	//cout<<"Succeeded "<<success<<" times"<<endl;
  	//if(success == 0) cout<<"Failed."<<endl;
  }
  double botchthresh = (double)0.5 * (double)maxtimes;
  if (botch >= botchthresh)
  {
            //cout<<"And a glitch occurred!"<<endl;
            }
            return success;
            
}

