#include "Item.h"

Item::Item() {}

Item::Item(string name,int part,int health,int attack,int defense) :
    Object(name,"Item") , health(health) , attack(attack) , defense(defense), part(part)  {}

int Item::getAttack(){
    return this->attack;
}

int Item::getDefense(){
    return this->defense;
}

int Item::getHealth(){
    return this->health;
}

int Item::getPart(){
    return this->part;
}

void Item::setPart(int p){
    this->part = p;
}

void Item::setAttack(int atk){
    this->attack = atk;
}

void Item::setDefense(int def){
    this->defense = def;
}

void Item::setHealth(int heal){
    this->health = heal;
}

void Item::showstatus(){
    cout << this->getName() << '\n';
    if(health > 0)
        cout << "> Health:" << health << '\n';
    if(attack > 0)
        cout << "> Attack:" << attack << '\n';
    if(defense > 0)
        cout << "> Defense:" << defense << '\n';
}

bool Item::operator == (Item& i2){
    return (i2.getName() == this->getName());
}

bool Item::triggerEvent(Object* o){
    Player* p = dynamic_cast<Player*>(o);
    cout << "There is " << this->getName() << ",do you want to pick it up?\n";
    cout << "Y.yes\n" << "N.no\n";
    char op; cin >> op;
    if(op == 'Y' || op == 'y'){
        p->addItem(*this);
        return true;
    }
    return false;
}
