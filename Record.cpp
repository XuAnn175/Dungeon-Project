#include "Record.h"

Record::Record(){}

void Record::savePlayer(Player* p,ofstream& ofs){
    ofs.open("saveplayer.txt");
    ofs << p->getName() << " " << p->getMoney() << " " << p->getMaxHealth() << " " << p->getCurrentHealth() << " " << p->getAttack() << " " << p->getDefense() << " ";
    ofs << p->getCurrentRoom()->getIndex() << " " << p->getPreviousRoom()->getIndex() << " " << (p->getInventory()).size() << " ";
    for(Item i : p->getInventory()){
        ofs << i.getName() << " " << i.getPart() << " " << i.getHealth() << " " << i.getAttack() << " " << i.getDefense() << " ";
    }
    ofs << (p->getequipment()).size() << " ";
    for(Item i : p->getequipment()){
        ofs << i.getName() << " " << i.getPart() << " " << i.getHealth() << " " << i.getAttack() << " " << i.getDefense() << " ";
    }
    ofs.close();
}

void Record::saveRooms(vector<Room*>& Rooms, ofstream& ofs){
    ofs.open("saverooms.txt");
    for(int i = 0; i <= 10; i++){
        ofs << Rooms[i]->getIndex() << " ";
        ofs << (Rooms[i]->getLeftRoom() == nullptr ? -1 : Rooms[i]->getLeftRoom()->getIndex()) << " ";
        ofs << (Rooms[i]->getUpRoom() == nullptr ? -1 : Rooms[i]->getUpRoom()->getIndex()) << " ";
        ofs << (Rooms[i]->getRightRoom() == nullptr ? -1 : Rooms[i]->getRightRoom()->getIndex()) << " ";
        ofs << (Rooms[i]->getDownRoom() == nullptr ? -1 : Rooms[i]->getDownRoom()->getIndex()) << " ";
        ofs << Rooms[i]->getislocked() << " " <<Rooms[i]->getIsExit() << " ";
        ofs << (Rooms[i]->getObjects()).size() << " ";
        for(Object* j : Rooms[i]->getObjects()){
            ofs << j->getName() << " " << j->getTag() << " ";
            if(j->getTag() == "Item"){
                Item* it = dynamic_cast<Item*>(j);
                ofs << it->getPart() << " " << it->getHealth() << " " << it->getAttack() << " " << it->getDefense() << " ";
            }
            if(j->getTag() == "Monster"){
                Monster* m = dynamic_cast<Monster*>(j);
                ofs << m->getCurrentHealth() << " " << m->getAttack() << " " << m->getDefense() << " " << m->getMoney() << " ";
            }
            if(j->getTag() == "NPC"){
                NPC* n = dynamic_cast<NPC*>(j);
                ofs << (n->getCommodity()).size() << " ";
                for(Item k : n->getCommodity()){
                    ofs << k.getName() << " " << k.getPart() << " " << k.getHealth() << " " << k.getAttack() << " " << k.getDefense() << " ";
                }
            }
        }
    }
    ofs.close();
}

void Record::loadRooms(vector<Room*>& Rooms,ifstream& ifs){
    ifs.open("saverooms.txt",ios::in);
    stringstream ss;
    ss << ifs.rdbuf();
    int c;
    Rooms.clear();
     for(int i = 0; i <= 10; i++){
        vector<Object*> v;
        Room* newroom = new Room(0,0,i,v);
        Rooms.push_back(newroom);
    }
    for(int i = 0; i <= 10; i++){
        ss >> c;
        ss >> c; if(c != -1) Rooms[i]->setLeftRoom(Rooms[c]);
        ss >> c; if(c != -1) Rooms[i]->setUpRoom(Rooms[c]);
        ss >> c; if(c != -1) Rooms[i]->setRightRoom(Rooms[c]);
        ss >> c; if(c != -1) Rooms[i]->setDownRoom(Rooms[c]);
        ss >> c; Rooms[i]->setislocked(c);
        ss >> c; Rooms[i]->setIsExit(c);
        ss >> c;
        vector<Object*> vec;
        for(int j = 0; j < c; j++){
            string name,type; ss >> name >> type;
            if(type == "Item"){
                int pt,hl,atk,def;
                ss >> pt >> hl >> atk >> def;
                Item* it = new Item(name,pt,hl,atk,def);
                vec.push_back(it);
            }
            if(type == "Monster"){
                int hl,atk,def,mon;
                ss >> hl >> atk >> def >> mon;
                Monster* m = new Monster(name,hl,atk,def,mon);
                vec.push_back(m);
            }
            if(type == "NPC"){
                string scr;
                if(i == 5)
                    scr = "aaaaaaaaaa\nIf you can answer the following question,then i will give sth you might want\n1*1=?\n";
                else if(i == 6)
                    scr = "hehehehe\nIf you can answer the following question,then i will give sth you might want\n0+1=?\n";
                vector<Item> com;
                int sz; ss >> sz;
                for(int k = 0; k < sz; k++){
                    string na;
                    int pt,hl,atk,def;
                    ss >> na >> pt >> hl >> atk >> def;
                    Item i = Item(na,pt,hl,atk,def);
                    com.push_back(i);
                }
                NPC* n = new NPC(name,scr,com);
                vec.push_back(n);
            }
        }
        Rooms[i]->setObjects(vec);
    }
    ifs.close();
}

void Record::loadPlayer(Player* p, vector<Room*>& Rooms,ifstream& ifs){
    ifs.open("saveplayer.txt",ios::in);
    stringstream ss;
    ss << ifs.rdbuf();
    string cur; int c;
    ss >> cur;p->setName(cur);
    ss >> c;  p->setMoney(c);
    ss >> c;  p->setMaxHealth(c);
    ss >> c;  p->setCurrentHealth(c);
    ss >> c;  p->setAttack(c);
    ss >> c;  p->setDefense(c);
    ss >> c;  p->setCurrentRoom(Rooms[c]);
    ss >> c;  p->setPreviousRoom(Rooms[c]);
    ss >> c;
    vector<Item> inv;
    for(int i = 0; i < c; i++){
        string na;
        int pt,heal,atk,def;
        ss >> na >> pt >> heal >> atk >> def;
        Item it = Item(na,pt,heal,atk,def);
        inv.push_back(it);
    }
    p->setInventory(inv);
    ss >> c;
    vector<Item> equ;
    for(int i = 0; i < c; i++){
        string na;
        int pt,heal,atk,def;
        ss >> na >> pt >> heal >> atk >> def;
        Item it = Item(na,pt,heal,atk,def);
        equ.push_back(it);
    }
    p->setequipment(equ);
    ifs.close();
}

void Record::saveToFile(Player* p, vector<Room*>& Rooms){
    ofstream ofp;
    savePlayer(p,ofp);
    ofp.close();
    ofstream ofr;
    saveRooms(Rooms,ofr);
    ofr.close();
}

void Record::loadFromFile(Player* p, vector<Room*>& Rooms){
    ifstream ifr;
    loadRooms(Rooms,ifr);
    ifstream ifp;
    loadPlayer(p,Rooms,ifp);
}
