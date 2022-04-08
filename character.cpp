#include "character.h"

int Character::getLife()
{
    return lifepoints;
}

void Character::setLife(int nb){
    lifepoints += nb;
}

void Character::setAttack(int num){
    attack -= num;
}

void Character::heal(int nb){
    lifepoints = nb;
}

