#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>

class Character
{
public:
    Character(QString name);
    int getLife(Character *player);
protected:
    int lifepoints;
    QString name;
};

#endif // CHARACTER_H
