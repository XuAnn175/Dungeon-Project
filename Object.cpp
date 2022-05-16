#include "Object.h"

Object::Object() {}

Object::Object(string Name,string Tag) : name(Name) , tag(Tag) {}

void Object::setName(string name){
    this->name = name;
}

void Object::setTag(string tag){
    this->tag = tag;
}

string Object::getName(){
    return this->name;
}

string Object::getTag(){
    return this->tag;
}


