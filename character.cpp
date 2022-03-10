#include "character.h"

Character::Character(QString player)
{
    lifepoints = 100;
    name = player;
}
int Character::getLife(Character *player)
{
    return player->lifepoints;
}

