#include <cstdlib>
#include <iostream>
#include <string>
#include "character.h"
#include "battle.h"
using namespace std;


int main(int argc, char *argv[])
{
    srand ( time(NULL) );
    Character you(100, 3, 5, 5, 5, 5, 5, "You"), enemy(150, 7, 2, 5, 2, 2, 2, "Ninjas"),
    chuckNorris(999, 9, 9, 9, 9, 9, 9, "Chuck"), echuckNorris(999, 9, 9, 9, 9, 9, 9, "RChuck");
    Battle dumBattle;
    dumBattle.run(echuckNorris, chuckNorris, 1);
    system("PAUSE");
    return EXIT_SUCCESS;
}

