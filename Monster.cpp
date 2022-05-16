#include "Monster.h"

Monster::Monster() {}

Monster::Monster(string name,int h,int atk,int def,int m)
    :GameCharacter(name,"Monster",h,atk,def,m) {}

void Monster::showstatus(){
    cout << "Status of Monster:\n";
    cout << this->getName() << '\n';
    cout << "> Health:" << this->getCurrentHealth() << "/" << this->getMaxHealth() << '\n';
    cout << "> Attack:" << this->getAttack() << '\n';
    cout << "> Defense:" << this->getDefense() << '\n';
}

bool Monster::triggerEvent(Object* o){
    cout << "There is a monster "<< this->getName() <<" in the current room\n";
    cout << "START FIGHTING!!!!\n";
    Player* p = dynamic_cast<Player*>(o);
    while(true){
        cout << "Choose Action\n" << "A.Fight the Monster\n" << "B.retreat\n";
        char op; cin >> op;
        if(op == 'A' || op == 'a'){
            this->setCurrentHealth(this->getCurrentHealth() - p->getAttack() + this->getDefense() );
            if(this->getCurrentHealth() <= 0){
                cout << "You win,the monster is dead!\n";
                p->increaseStates(5,10,1,this->getMoney());
                return true;
            }
            cout << "You attack the monster,its remaining health:" << this->getCurrentHealth() << '\n';
            p->setCurrentHealth( (p->getCurrentHealth() - this->getAttack() + p->getDefense() ) );
            if(p->getCurrentHealth() <= 0){
                cout << "You are defeated by the monster!\n";
                return false;
            }
            cout << "You are attacked by the monster,your remaining health:" << p->getCurrentHealth() << '\n';
        }
        else{
            p->changeRoom(p->getPreviousRoom());
            return false;
        }
    }
}


