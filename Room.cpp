#include "Room.h"

Room::Room() {}

Room::Room(bool isexit,bool isLocked,int ind,vector<Object*> vec){
    isExit = isexit;
    islocked = isLocked;
    index = ind;
    objects = vec;
    upRoom = nullptr;
    downRoom = nullptr;
    leftRoom = nullptr;
    rightRoom = nullptr;
}

void Room::setUpRoom(Room* r){
    upRoom = r;
}

void Room::setDownRoom(Room* r){
    downRoom = r;
}

void Room::setLeftRoom(Room* r){
    leftRoom = r;
}

void Room::setRightRoom(Room* r){
    rightRoom = r;
}

void Room::setIndex(int ind){
    index = ind;
}

void Room::setIsExit(bool is){
    isExit = is;
}

void Room::setislocked(bool is){
    islocked = is;
}

void Room::setObjects(vector<Object*> vec){
    objects = vec;
}

bool Room::popObject(Object* obj){
    auto it = find(objects.begin() ,objects.end() , obj);
    objects.erase(it);
}

int Room::getIndex(){
    return index;
}

bool Room::getIsExit(){
    return isExit;
}

bool Room::getislocked(){
    return islocked;
}

Room* Room::getUpRoom(){
    return upRoom;
}

Room* Room::getDownRoom(){
    return downRoom;
}

Room* Room::getLeftRoom(){
    return leftRoom;
}

Room* Room::getRightRoom(){
    return rightRoom;
}

vector<Object*> Room::getObjects(){
    return objects;
}
