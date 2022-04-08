#ifndef CHARACTER_H
#define CHARACTER_H

#define EVAC 10

#include <QString>
#include <list>

using namespace std;

template <class T>
QString getName(T x){
    return x->name;
}

class Character
{
public:
    Character(int lp,int a):lifepoints(lp),attack(-a) {}
    int getLife();
    void heal(int nb);
    void setAttack(int num);
    void setLife(int nb);

protected:
    int lifepoints;
    int attack;
};

class attack_{
public :
    virtual void Attack(Character* p){}
};

class potion{
protected :
    QString name;
public :
    void giveName(QString name){
        this->name = name;
    }

    QString Name(potion p){
        return p.name;
    }

    void health(int nb, Character* x){
        x->setLife(nb);
    }

    void strength(int nb, Character* x){
        x->setAttack(nb);
    }
};

class player : public Character, virtual public attack_, public potion
{
private :
    list<potion> inventory;
    QString name;
public :
    player(QString n, int lp, int a):Character(lp,a){
        name = n;
        inventory = {};
    }

    void addInventory(potion p){
        inventory.push_back(p);
    }

    QString getName(player p){
        return name;
    }

    potion getObj(QString name){
       list<potion>::iterator it = inventory.begin();
       while(it!=inventory.end() && (Name(*it))!=name){
           it++;
       }
       return *it;
    }

    void Attack(Character *character)
    {
        character->setLife(attack);
    }

    void useObj(potion p){
        QString obj = Name(p);
        int rndm = rand()%2;
        switch(rndm){
            case 0: rndm = 20; break;
        case 1: rndm = -20; break;
        }

        if(obj=="mystery potion")
            health(rndm,this);
        if(obj=="full heal")
            health(100-lifepoints,this);
        if(obj=="strength potion")
            strength(20,this);
    }
};

class monster : public Character, virtual public attack_{
private :

public :
    QString name;

    monster(QString n, int lp, int a):Character(lp,a){
        name = n;
    }

    QString getName(monster m){
        return m.name;
    }

    void Attack(Character *character)
    {
        int rnd = rand()%100;
        if(rnd>EVAC)
            character->setLife(this->attack);
    }
};

#endif // CHARACTER_H
