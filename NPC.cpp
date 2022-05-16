#include "NPC.h"

NPC::NPC() {}

NPC::NPC(string name,string script,vector<Item> vec) :
    GameCharacter(name,"NPC",0,0,0,0) , script(script) , commodity(vec) {}

void NPC::listCommodity(){
    for(Item i : commodity){
        cout << i.getName() << '\n';
        cout << "Attack:" << i.getAttack() << '\n';
        cout << "Health:" << i.getHealth() << '\n';
        cout << "Defense:"<< i.getDefense() << '\n';
        cout << '\n';
    }
}

void NPC::setScript(string scr){
    script = scr;
}

void NPC::setCommodity(vector<Item> vec){
    commodity = vec;
}

string NPC::getScript(){
    return script;
}

vector<Item> NPC::getCommodity(){
    return commodity;
}

bool NPC::triggerEvent(Object* o){
    Player* p = dynamic_cast<Player*>(o);
    cout << "Hello! I'm " << this->getName() << '\n' << script;
    int ans; cin >> ans;
    if(ans == 1){
        cout << "Congrats! Your answer is right! The following items are your rewards!\n";
        listCommodity();
        for(Item i : commodity)
            p->addItem(i);
        return true;
    }
    else
        return false;
}
