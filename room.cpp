#include "room.h"

Room::Room(QString description){
    this->description = description;
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
