#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Object.h"
#include "Player.h"
using namespace std;

class Player;

class Item: public Object
{
private:
    int health,attack,defense,part;
public:
    Item();
    Item(string, int ,int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.         */
    bool triggerEvent(Object*);
    bool operator ==(Item&);
    void showstatus();
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    int getPart();
    void setPart(int);
    void setHealth(int);
    void setAttack(int);
    void setDefense(int);
};

#endif // ITEM_H_INCLUDED
