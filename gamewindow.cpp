#include "mainwindow.h"
#include "gamewindow.h"
#include "ui_gamewindow.h"

using namespace std;

Room* current;
list<Room*> rooms;
QString word;
int tries = 0;

GameWindow::GameWindow(QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    player = new class player(name,100,20);
    ui->Life->setValue(player->getLife());
    ui->Name->setHtml("<p align='center' style='font-size:20px;font-weight:bold;'>"+name+"</p>");
    ui->Story->append("Hello traveller, and welcome to Ork!");
    ui->Story->append("Many have come to this dungeon, seeking glory, but few have survived.\n"
                      "Fortunately we now have a map. So take it, go solve all the puzzles and conquer the dungeon.\n"
                      "Good Luck friend.\n\n");
    createRooms();
    wordle = new Wordle();
}

//Creating the dungeon

void GameWindow::createRooms(){
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k;
    a = new Room("a","You are in the first room of the dungeon.\n"
                 "Looking around you see nothing except a door leading to the north.\n","",0,false);
    b = new Room("b","The room is very dark, with only glowing moss to lighten it."
                 ,"",1,true);
    c = new Room("c","You now have three doors in front of you : in the west, in the north and in the east.","mystery potion",0,false);
    d = new Room("d","You enter the room, but see nothing.","full heal",0,false);
    e = new Room("e","You enter the room, but there seems to be nothing nothing.","strength potion",0,false);
    f = new Room("f","There are glowing stones on the wall. Thanks to them,\n"
                 "you see the door leading to the east.","",0,false);
    g = new Room("g","The room seems empty, with a door facing south.","",1,false);
    h = new Room("h","This the darkest room you've seen yet.","full heal",0,false);
    i = new Room("i","You are close to the end, and there are two doors facing south and east.","",0,true);
    j = new Room("j","The room room is very narrow and look like a corridor leading to the west.","",0,false);
    k = new Room("k","Upon entering the room, the door closes and you get trap in the boss room.\n"
                 "Defeat the Ork and survive or die.","",2,false);
    //direction N,E,S,W
    a->setExits(c, NULL, NULL, NULL);
    b->setExits(e, c, NULL, NULL);
    c->setExits(f, d, a, b);
    d->setExits(NULL, NULL, NULL, c);
    e->setExits(NULL, NULL, b, NULL);
    f->setExits(NULL, g, c, NULL);
    g->setExits(j, NULL, NULL, f);
    h->setExits(NULL, i, NULL, NULL);
    i->setExits(k, j, NULL, h);
    j->setExits(NULL,g,NULL,i);
    k->setExits(NULL,NULL,i,NULL);

    rooms = {a,b,c,d,e,f,g,h,i,j,k};
    current = a;
    ui->Story->append(a->getDescription());
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_Life_valueChanged(int value)
{
    if (value == 0)
    {
        MainWindow *newG = new MainWindow();
        newG->show();
        close();
    }
}

//Map

void GameWindow::on_Map_clicked()
{
    QString map = "        [k]\n"
                  "         |\n"
                  "[h] --- [i] --- [j]\n"
                  "                 |\n"
                  "[e]     [f] --- [g]\n"
                  " |       |        \n"
                  "[b] --- [c] --- [d]\n"
                  "         |\n"
                  "        [a]\n";
    ui->Story->append(map);
    ui->Story->append("You are currently in "+current->name);
}


//Movements

void GameWindow::on_North_clicked()
{
    if(!isMonster(current)){
        if (current->isWordle()){
            if(tries==0)
                word = wordle->getWord();
            ui->Enter->setEnabled(true);
            ui->textEdit->setEnabled(true);
            ui->Story->append("To get pass this door you need to guess the 5 letters long password.\n"
                              "Be carefull, you have 5 tries before the password change.");
        }
        else{
            Room* next = current->nextRoom("north");
            if (next != NULL) {
                current = next;
                ui->Story->append(current->getDescription());
            }
            else {
                ui->Story->append("There is a wall obstructing your path.\n");
            }
        }
    }
    else
        ui->Story->append("The room in the north is blocked by a goblin.");
}

void GameWindow::on_South_clicked()
{
    Room* next = current->nextRoom("south");
    if (next != NULL) {
        current = next;
        ui->Story->append(current->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_East_clicked()
{
    Room* next = current->nextRoom("east");
    if (next != NULL) {
        current = next;
        ui->Story->append(current->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_West_clicked()
{
    Room* next = current->nextRoom("west");
    if (next != NULL) {
        current = next;
        ui->Story->append(current->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_Take_clicked()
{
    potion *obj = current->getObject();
    QString name = obj->Name(*obj);
    if(name != ""){
        ui->Inventory->addItem(name);
        player->addInventory(*obj);
        current->setObject();
    }
    else
        ui->Story->append("There is nothing in this room.");
}

void GameWindow::on_Inventory_itemDoubleClicked(QListWidgetItem *item)
{
    player->useObj(player->getObj(item->text()));
    delete item;
    ui->Life->setValue(player->getLife());
}


void GameWindow::on_Attack_clicked()
{
    if(isMonster(current))
    {
        if((getMonster(current))->getLife()<=0){
            if(getName(getMonster(current))=="Ork"){
                MainWindow *newG = new MainWindow();
                newG->show();
                close();
            }
            ui->Story->append("The "+getName(getMonster(current))+" has been slayed.");
            current->setIsMonster(false);
        }
        else{
            player->Attack(getMonster(current));
            int x = (getMonster(current))->getLife();
            ui->Story->append("The "+getName(getMonster(current))+" has "+QString::number((x<0)?0:x)+" remaining.");
            int life = player->getLife();
            getMonster(current)->Attack(player);
            if(player->getLife()==life)
                ui->Story->append("You successfully dodged the attack.");
            ui->Life->setValue((player->getLife()>=0)?player->getLife():0);
        }
    }
    else
        ui->Story->append("There are no ennemies.");
}

monster* getMonster(Room* current){
    return current->monster;
}

bool isMonster(Room* current){
    return current->ismonster;
}

void GameWindow::check(QString guess,letters** isRight){
    QString::pointer it = guess.begin();
    QString::pointer it2;
    int pos1 = 0;
    int pos2;
    letters* l;
    while(it!=guess.end()){
        l = new letters(*it, pos1);
        it2 = word.begin();
        pos2 = 0;
        while(it2!=word.end()){
            if(*it==*it2){
                if(pos1==pos2)
                    l->rightP = true;
                else
                    l->misplaced = true;
            }
            pos2++;
            it2++;
        }
        isRight[pos1] = l;
        it++;
        pos1++;
    }
}


void GameWindow::sort(letters** sort){
    int to_check;
    int x;
    for(int i = 0;i<5;i++){
        x = wordle->times(sort[i]->letter,word);
        to_check = (x>0) ? x-1 : x;
        for(int j = i+1;j<5;j++){
            if(sort[i]->letter == sort[j]->letter && to_check==0){
                if(sort[j]->rightP)
                    sort[i]->misplaced = false;
                sort[j]->misplaced = false;
            }
        }
    }
}

void GameWindow::on_Enter_clicked()
{
    tries++;
    if(tries>5){
        tries = 0;
        ui->Story->append("You failed to find the word. Try again.");
        word = wordle->getWord();
    }
    QString guess = ui->textEdit->toPlainText();
    QString text = "";

    if (guess.size()==word.size())
    {
        if(guess==word){
            ui->Story->append("Congratulations ! You passed.");
            current->setWordle(false);
            ui->Enter->setEnabled(false);
            ui->textEdit->setEnabled(false);
            tries = 0;
        }
        else{
            letters* right[5];
            check(guess,right);
            sort(right);
            QString arr[5] = {"","","","",""};
            letters* l;
            for(int i = 0; i<5;i++){
                l = right[i];
                int let = l->place;
                arr[let] = l->letter;
                if(l->rightP){
                    arr[let] = "<span style='background-color:green;'>";
                    arr[let] += l->letter;
                    arr[let] += "</span>";
                }
                if(l->misplaced){
                    arr[let] = "<span style='background-color:yellow;'>";
                    arr[let] += l->letter;
                    arr[let] += "</span>";
                }
            }
            for(int i = 0;i<5;i++){
                text.append(arr[i]);
            }
            ui->Story->append(text);
        }
    }
    else
        ui->Story->append("The word must be 5 letters long.");
}

