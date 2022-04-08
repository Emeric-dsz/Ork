#include "room.h"

Room::Room(QString name, QString description, QString object, int monster, bool wordle){
    this->name = name;
    this->description = description;
    this->object = new potion();
    this->object->giveName(object);
    ismonster = monster;
    if(monster == 1)
        this->monster = new class monster("Goblin",100,10);
    else
        this->monster = new class monster("Ork",200,20);
    iswordle = wordle;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west){
    if (north!=NULL)
        exits["north"] = north;
    if (south!=NULL)
        exits["south"] = south;
    if (east!=NULL)
        exits["east"] = east;
    if (west!=NULL)
        exits["west"] = west;
}

QString Room::getDescription(){
    return description;
}

Room* Room::nextRoom(QString direction){
    return exits[direction];
}

QString Room::getMap(){
    return "[" + this->description + "]";
}

potion* Room::getObject(){
    return object;
}

void Room::setObject(){
    object->giveName("");
}

void Room::setIsMonster(bool is){
    ismonster = is;
}

bool Room::isWordle(){
    return iswordle;
}
void Room::setWordle(bool set){
    iswordle = set;
}
