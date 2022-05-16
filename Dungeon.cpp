#include "Dungeon.h"

Dungeon::Dungeon(){}

void Dungeon::runDungeon(){
    cout << "Do you want to load previous data?\n";
    cout << "A.Yes\nB.No\n";
    char op; cin >> op;
    if(op == 'Y' || op == 'y')
       rec.loadFromFile(&player,rooms);
    else
        startGame();
    while(true){
        vector<Object*> objs = (player.getCurrentRoom())->getObjects();
        chooseAction(objs);
        if(checkGameLogic())
            break;
    }
}

void Dungeon::startGame(){
    createPlayer();
    createMap();
}

void Dungeon::createPlayer(){
    cout << "Enter your name:\n";
    string name; cin >> name;
    player = Player(name,200,30,1,100);
}

void Dungeon::createMap(){
    for(int i = 0; i < 10; i++){
        vector<Object*> v;
        Room* newroom = new Room(0,0,i,v);
        rooms.push_back(newroom);
    }
    vector<Object*> vec;
    Room* newroom = new Room(1,0,10,vec);
    rooms.push_back(newroom);
    rooms[8]->setislocked(1);
    //set map
    rooms[0]->setUpRoom(rooms[1]);
    player.setCurrentRoom(rooms[0]);
    rooms[1]->setRightRoom(rooms[2]);
    rooms[1]->setDownRoom(rooms[0]);
    rooms[2]->setLeftRoom(rooms[1]);
    rooms[2]->setUpRoom(rooms[7]);
    rooms[2]->setRightRoom(rooms[3]);
    rooms[2]->setDownRoom(rooms[5]);
    rooms[3]->setLeftRoom(rooms[2]);
    rooms[3]->setRightRoom(rooms[8]);
    rooms[3]->setUpRoom(rooms[6]);
    rooms[3]->setDownRoom(rooms[4]);
    rooms[4]->setLeftRoom(rooms[5]);
    rooms[4]->setUpRoom(rooms[3]);
    rooms[5]->setUpRoom(rooms[2]);
    rooms[5]->setRightRoom(rooms[4]);
    rooms[6]->setDownRoom(rooms[3]);
    rooms[6]->setLeftRoom(rooms[7]);
    rooms[7]->setRightRoom(rooms[6]);
    rooms[7]->setDownRoom(rooms[2]);
    rooms[8]->setLeftRoom(rooms[3]);
    rooms[8]->setRightRoom(rooms[9]);
    rooms[9]->setRightRoom(rooms[10]);
    rooms[9]->setLeftRoom(rooms[8]);
    rooms[10]->setLeftRoom(rooms[9]);
    //default equipment
    Item d_0 = Item("cap",0,0,0,1);
    Item d_1 = Item("vast",1,0,0,1);
    Item d_2 = Item("knife",2,0,5,0);
    Item d_3 = Item("plate",3,0,0,1);
    Item d_4 = Item("Potion",-1,25,0,0);
    player.equip(d_0);
    player.equip(d_1);
    player.equip(d_2);
    player.equip(d_3);
    player.addItem(d_4);
    player.addItem(d_4);
    //set objs
    vector<Object*> v1;
    Item* i_1 = new Item("Sword",2,0,10,0);
    Monster* m_1 = new Monster("rock",100,25,3,50);
    v1.push_back(i_1);
    v1.push_back(m_1);
    rooms[1]->setObjects(v1);

    vector<Object*> v2;
    Item* i_2 = new Item("armour",1,0,0,2);
    Monster* m_2 = new Monster("bird",100,10,5,50);
    v2.push_back(i_2);
    v2.push_back(m_2);
    rooms[2]->setObjects(v2);

    vector<Object*> v7;
    Item* i_7 = new Item("Potion",-1,25,0,0);
    v7.push_back(i_7);
    rooms[7]->setObjects(v7);
    rooms[4]->setObjects(v7);

    vector<Object*> v5;
    vector<Item> v_5;
    Item i_5 = Item("SuperSword",2,5,30,0);
    v_5.push_back(i_5);
    i_5 = Item("SuperHelmet",0,5,0,3);
    v_5.push_back(i_5);
    string s_5 = "aaaaaaaaaa\nIf you can answer the following question,then i will give sth you might want\n1*1=?\n";
    NPC* n_5 = new NPC("Adam",s_5,v_5);
    v5.push_back(n_5);
    rooms[5]->setObjects(v5);

    vector<Object*> v3;
    Monster* m_3 = new Monster("wolf",150,40,10,100);
    v3.push_back(m_3);
    rooms[3]->setObjects(v3);

    vector<Object*> v9;
    Monster* m_9 = new Monster("Boss",500,30,10,0);
    v9.push_back(m_9);
    rooms[9]->setObjects(v9);

    vector<Object*> v6;
    vector<Item> v_6;
    Item i_6 = Item("SuperShield",3,10,0,3);
    v_6.push_back(i_6);
    i_6 = Item("Key",-1,0,0,0);
    v_6.push_back(i_6);
    string s_6 = "hehehehe\nIf you can answer the following question,then i will give sth you might want\n0+1=?\n";
    NPC* n_6 = new NPC("joker",s_6,v_6);
    v6.push_back(n_6);
    rooms[6]->setObjects(v6);
}


bool Dungeon::checkGameLogic(){
    if(player.checkIsDead()){
        cout << "Game Over!!!\n";
        return true;
    }
    else if( (player.getCurrentRoom())->getIsExit() && (rooms[9]->getObjects()).empty() ){
        cout << "Victory!!!\n";
        return true;
    }
    return false;
}

void Dungeon::handleMovement(){
    cout << "Where do you want to go?\n";
    if(player.getCurrentRoom()->getUpRoom() != nullptr){
        cout << "A.Go up";
        if( player.getCurrentRoom()->getUpRoom()->getislocked() )
            cout << "(locked)";
        cout << '\n';
    }
    if((player.getCurrentRoom())->getDownRoom() != nullptr){
        cout << "B.Go down";
        if( player.getCurrentRoom()->getDownRoom()->getislocked() )
            cout << "(locked)";
        cout << '\n';
    }
    if((player.getCurrentRoom())->getLeftRoom() != nullptr){
        cout << "C.Go left";
        if( player.getCurrentRoom()->getLeftRoom()->getislocked() )
            cout << "(locked)";
        cout << '\n';
    }
    if((player.getCurrentRoom())->getRightRoom() != nullptr){
        cout << "D.Go right";
        if( player.getCurrentRoom()->getRightRoom()->getislocked() )
            cout << "(locked)";
        cout << '\n';
    }

    char operation;
    cin >> operation;
    int num_of_key = 0,use_key = 0;
    for(Item i : player.getInventory())
        if(i.getName() == "Key")
            num_of_key++;

    switch(operation){
        case 'a': case 'A':
            if(!(player.getCurrentRoom()->getUpRoom()->getislocked()))
                player.changeRoom( (player.getCurrentRoom())->getUpRoom() );
            else{
                if(num_of_key){
                    player.getCurrentRoom()->getUpRoom()->setislocked(0);
                    player.changeRoom( (player.getCurrentRoom())->getUpRoom() );
                    use_key = 1;
                }
                else
                    cout << "Illegal! you don't have any key!!\n";
            }
            break;
        case 'b': case 'B':
            if(!(player.getCurrentRoom()->getDownRoom()->getislocked()))
                player.changeRoom( (player.getCurrentRoom())->getDownRoom() );
            else{
                if(num_of_key){
                    player.getCurrentRoom()->getDownRoom()->setislocked(0);
                    player.changeRoom( (player.getCurrentRoom())->getDownRoom() );
                    use_key = 1;
                }
                else
                    cout << "Illegal! you don't have any key!!\n";
            }
            break;
        case 'c': case 'C':
            if(!(player.getCurrentRoom()->getLeftRoom()->getislocked()))
                player.changeRoom( (player.getCurrentRoom())->getLeftRoom() );
            else{
                if(num_of_key){
                    player.getCurrentRoom()->getLeftRoom()->setislocked(0);
                    player.changeRoom( (player.getCurrentRoom())->getLeftRoom() );
                    use_key = 1;
                }
                else
                    cout << "Illegal! you don't have any key!!\n";
            }
            break;
        case 'd': case 'D':
            if(!(player.getCurrentRoom()->getRightRoom()->getislocked()))
                player.changeRoom( (player.getCurrentRoom())->getRightRoom() );
            else{
                if(num_of_key){
                    player.getCurrentRoom()->getRightRoom()->setislocked(0);
                    player.changeRoom( (player.getCurrentRoom())->getRightRoom() );
                    use_key = 1;
                }
                else
                    cout << "Illegal! you don't have any key!!\n";
            }
            break;
    }
    if(use_key){
        for(Item i : player.getInventory())
            if(i.getName() == "Key"){
                player.equip(i);
                break;
            }
    }
}

void Dungeon::chooseAction(vector<Object*> objs){
    cout << "What do you want to do?\n";
    cout << "A.Move\n" << "B.Check Status\n" << "C.Talk to Shop\n" << "D.Open Backpack\n" << "E.Save file\n";
    char ch = 'F';
    bool mon = 0;
    for(Object* i : objs){
        if(i->getTag() == "Monster"){
            cout << ch << ".Fight with Monster.\n";
        }
        if(i->getTag() == "NPC")
            cout << ch << ".Interact with NPC.\n";
        if(i->getTag() == "Item")
            cout << ch << "." << "Open the Chest\n";
        ch = char(ch + 1);
    }
    char operation;
    cin >> operation;
    switch(operation){
        case 'a': case 'A':{
            handleMovement();
            break;
        }
        case 'b': case 'B':{
            player.triggerEvent(&player);
            break;
        }
        case 'c': case 'C':{
            //talk to shop
            vector<Item> shop;
            vector<int> cost;
            Item i = Item("Sword II",2,0,20,1);
            shop.push_back(i);
            cost.push_back(75);
            i = Item("Shield II",3,5,0,2);
            shop.push_back(i);
            cost.push_back(75);
            i = Item("Armour II",1,5,0,2);
            shop.push_back(i);
            cost.push_back(75);
            i = Item("Potion",-1,25,0,0);
            shop.push_back(i);
            cost.push_back(30);
            cout << "-------------SHOP-------------\n";
            int ind = 1;
            for(Item i : shop){
                cout << ind << ".";
                i.showstatus();
                cout << cost[ind-1] << "$\n";
                ind++;
            }
            cout << '\n';
            cout << "What do you want do buy? (or enter 0 to exit)\n";
            cout << "Your current money:" << player.getMoney() << "$\n";
            while(cin >> ind && ind){
                if(player.getMoney() >= cost[ind-1]){
                    player.setMoney( (player.getMoney() - cost[ind-1]) );
                    player.addItem(shop[ind-1]);
                }
                else{
                    cout << "You don't have enough money\n";
                }
                 cout << "Your current money:" << player.getMoney() << "$\n";
            }
            break;
        }
        case 'd': case 'D':{
            vector<Item> obj = player.getInventory();
            int ind = 1;
            for(Item i : obj){
                cout << ind++ << ".";
                i.showstatus();
            }
            cout << "Which one do you want to equip? (or enter 0 to exit)\n";
            cin >> ind;
            if(ind > 0)
                player.equip( obj[ind - 1] );
            break;
        }
         case 'e': case 'E':{
            rec.saveToFile(&player,rooms);;
            break;
        }
        default:
            int ind = isupper(operation) ? (operation - 'F') : (operation - 'f');
            handleEvent(objs[ind]);
            break;
    }
}

void Dungeon::handleEvent(Object* obj){
     // obj might be NPC,Monster,Item
     if(obj->triggerEvent(&player))
        player.getCurrentRoom()->popObject(obj);
}
