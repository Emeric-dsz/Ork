#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QString name, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    Character *player = new Character(name);
    ui->Life->setValue(player->getLife(player));
    ui->Name->setHtml("<p align='center' style='font-size:20px;font-weight:bold;'>"+name+"</p>");
    ui->Story->append("Hello traveller, and welcome to Ork!");
    ui->Story->append("Many have come to this dungeon, seeking glory, but few have survived.\n"
                      "Fortunately we now have a map. So take it, go defeat the Ork and conquer the dungeon.\n"
                      "Good Luck friend.\n\n");
    createRooms();
}

//Creating the dungeon

void GameWindow::createRooms(){
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    a = new Room("You are in the first room of the dungeon.\n"
                 "Looking around you see nothing except a door leading to the north.\n");
    b = new Room("b");
    c = new Room("You now have three doors in front of you : in the west, in the north and in the east.\n"
                 "But watching more carefully you find an object on the ground.\n");
    d = new Room("d");
    e = new Room("e");
    f = new Room("f");
    g = new Room("g");
    h = new Room("h");
    i = new Room("i");
    j = new Room("j");
    //direction N,E,S,W
    a->setExits(c, NULL, NULL, NULL);
    b->setExits(e, c, NULL, NULL);
    c->setExits(f, d, a, b);
    d->setExits(g, NULL, NULL, c);
    e->setExits(h, f, b, NULL);
    f->setExits(i, g, c, e);
    g->setExits(j, NULL, d, f);
    h->setExits(NULL, i, e, NULL);
    i->setExits(NULL, j, f, h);
    j->setExits(NULL,NULL,g,i);

    rooms = {a,b,c,d,e,f,g,h,i,j};
    currentRoom = a;
    ui->Story->append(a->getDescription());
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_Ouch_clicked()
{
    ui->Life->setValue(ui->Life->value() - 10);
}


void GameWindow::on_Life_valueChanged(int value)
{
    if (value == 0)
        QApplication::quit();
}

//Map

void GameWindow::on_Map_clicked()
{
    int currentLevel = 0;
    QString map = "[h] --- [i] --- [j]\n"
                  "  |        |        |\n"
                  "[e] --- [f] --- [g]\n"
                  "  |        |        |\n"
                  "[b] --- [c] --- [d]\n"
                  "           |\n"
                  "        [Entry]\n";
    ui->Story->append(map);
}


//Movements

void GameWindow::on_North_clicked()
{
    Room* next = currentRoom->nextRoom("north");
    if (next != NULL) {
        currentRoom = next;
        ui->Story->append(currentRoom->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_South_clicked()
{
    Room* next = currentRoom->nextRoom("south");
    if (next != NULL) {
        currentRoom = next;
        ui->Story->append(currentRoom->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_East_clicked()
{
    Room* next = currentRoom->nextRoom("east");
    if (next != NULL) {
        currentRoom = next;
        ui->Story->append(currentRoom->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_West_clicked()
{
    Room* next = currentRoom->nextRoom("west");
    if (next != NULL) {
        currentRoom = next;
        ui->Story->append(currentRoom->getDescription());
    }
    else {
        ui->Story->append("There is a wall obstructing your path.\n");
    }
}


void GameWindow::on_Take_clicked(bool checked)
{
}

