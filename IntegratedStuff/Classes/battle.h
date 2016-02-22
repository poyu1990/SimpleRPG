#include <cstdlib>
#include <iostream>
#include "character.h"
#include "attack.h"
using namespace std;
struct initList
{
       int init, id;
       Character person;
       string name;
};


class Battle
{
      public:
             attack atkL;
Battle();
~Battle();
int diceRoll(int number);
bool attackRoll(int attack, int defense);
int attackTarget(Character attacker, Character &target, int attkNum);
//void run(Character you, Character them, int num);
};


