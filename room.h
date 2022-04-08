#ifndef ROOM_H
#define ROOM_H

#include "gamewindow.h"

#include <QString>
#include <map>

using namespace std;

class potion;
class monster;
class Wordle;
class Room
{
private:
    potion* object;
    QString description;
    monster *monster;
    map<QString, Room*> exits;
    bool ismonster;
    bool iswordle;

public:
    Room(QString name, QString description, QString object, int monster, bool wordle);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    QString getDescription();
    Room* nextRoom(QString direction);
    QString getMap();
    potion* getObject();
    void setObject();
    void setIsMonster(bool is);
    bool isWordle();
    void setWordle(bool set);
    QString name;

    friend class monster* getMonster(Room* current);
    friend bool isMonster(Room* current);
};

#endif // ROOM_H
