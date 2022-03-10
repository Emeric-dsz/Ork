#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <map>

using namespace std;

class Room
{
private:
    QString name;
    QString description;
    map<QString, Room*> exits;
public:
    Room(QString description);
    void setExits(Room *north, Room *east, Room *south, Room *west);
    QString getDescription();
    Room* nextRoom(QString direction);
    QString getMap();
};

#endif // ROOM_H
