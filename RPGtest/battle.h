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
Battle::Battle();
Battle::~Battle();
int Battle::diceRoll(int number);
bool Battle::attackRoll(int attack, int defense);
int Battle::attackTarget(Character attacker, Character &target, int attkNum);
void Battle::run(Character you, Character them, int num);
};


