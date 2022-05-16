#include "Player.h"

Player::Player() {}

Player::Player(string name,int h,int a,int d,int m) :
    GameCharacter(name,"player",h,a,d,m) {}

void Player::addItem(Item newItem){
    inventory.push_back(newItem);
}

void Player::increaseStates(int dh,int da,int dd,int dm){
    this->setAttack( (this->getAttack() + da) );
    this->setCurrentHealth( min( (this->getCurrentHealth() + dh) , this->getMaxHealth()) ) ;
    this->setDefense( (this->getDefense() + dd) );
    this->setMoney( (this->getMoney() + dm) );
}

void Player::changeRoom(Room* next){
    previousRoom = currentRoom;
    currentRoom = next;
}

void Player::setCurrentRoom(Room* cur){
    currentRoom = cur;
}

void Player::setPreviousRoom(Room* prev){
    previousRoom = prev;
}

void Player::setInventory(vector<Item> Inventory){
    inventory = Inventory;
}

void Player::setequipment(vector<Item> equ){
    equipment = equ;
}

void Player::equip(Item i){
    for(int j = 0; j < inventory.size(); j++)
        if(inventory[j] == i){
            inventory.erase(inventory.begin() + j);
            break;
        }
    if(i.getName() == "Key")
        return;
    if(i.getName() == "Potion"){
        this->increaseStates(i.getHealth(), i.getAttack(), i.getDefense(),0);
        return;
    }
    bool change = 0;
    for(int j = 0; j < equipment.size(); j++){
        if(equipment[j].getPart() == i.getPart()){
            this->increaseStates( -(equipment[j].getHealth()) , -(equipment[j].getAttack()) , -(equipment[j].getDefense()) , 0);
            change = 1;
            inventory.push_back(equipment[j]);
            equipment.erase( equipment.begin() + j );
            this->increaseStates(i.getHealth(), i.getAttack(), i.getDefense(),0);
            equipment.push_back(i);
            break;
        }
    }
    if(!change){
        equipment.push_back(i);
        this->increaseStates(i.getHealth(), i.getAttack(), i.getDefense(),0);
    }

}

Room* Player::getCurrentRoom(){
    return currentRoom;
}

Room* Player::getPreviousRoom(){
    return previousRoom;
}

vector<Item> Player::getInventory(){
    return inventory;
}

vector<Item> Player::getequipment(){
    return equipment;
}

bool Player::triggerEvent(Object* p){
    cout << "Status:\n";
    cout << this->getName() << '\n';
    cout << "> Health:" << this->getCurrentHealth() << "/" << this->getMaxHealth() << '\n';
    cout << "> Attack:" << this->getAttack() << '\n';
    cout << "> Defense:" << this->getDefense() << '\n';
    cout << "> Money:" << this->getMoney() << '\n';
    //show items
    cout << "\nYour current equipment:\n";
    for(Item i : equipment)
        i.showstatus();
    cout << '\n';
    return false;
}
