#include "GameCharacter.h"

GameCharacter::GameCharacter() {}

GameCharacter::GameCharacter(string name,string tag,int mxh,int atk,int def,int m) :
    Object(name,tag) , maxHealth(mxh) , currentHealth(mxh) , attack(atk) , defense(def) , money(m) {} // tag = monster player NPC

bool GameCharacter::checkIsDead(){
    return (this->currentHealth <= 0);
}

void GameCharacter::setAttack(int atk){
    this->attack = atk;
}

void GameCharacter::setMaxHealth(int mx){
    this->maxHealth = mx;
}

void GameCharacter::setCurrentHealth(int cur){
    this->currentHealth = min(cur,this->getMaxHealth());
}

void GameCharacter::setDefense(int def){
    this->defense = def;
}

void GameCharacter::setMoney(int m){
    this->money = m;
}

int GameCharacter::getMoney(){
    return this->money;
}

int GameCharacter::getAttack(){
    return this->attack;
}

int GameCharacter::getCurrentHealth(){
    return this->currentHealth;
}

int GameCharacter::getMaxHealth(){
    return this->maxHealth;
}

int GameCharacter::getDefense(){
    return this->defense;
}



