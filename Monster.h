#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"
using namespace std;

class Monster: public GameCharacter
{
    private:
    public:
        Monster();
        Monster(string,int,int,int,int);
        void showstatus();
        /* Virtual function that you need to complete   */
        /* In Monster, this function should deal with   */
        /* the combat system.                           */
        bool triggerEvent(Object*);
};


#endif // ENEMY_H_INCLUDED
