
#ifndef _soldier_H
#define _soldier_H

#include <iostream>

class Soldier
{
protected:
    int player, lifePoints, damagePerActivity, foolLife;

public:
    Soldier(int player) : player(player)
    {
        std::cout << "Soldier constructor" << std::endl;
    }

    Soldier(int player, int lifePoint, int damagePerActivity)
        : player(player), lifePoints(lifePoint), damagePerActivity(damagePerActivity), foolLife(lifePoints)
    {
        // std::cout << "Soldier constructor" << std::endl;
    }

    ~Soldier() {}

    //seters:

    void setLifePoints(int newPoints)
    {
        lifePoints = newPoints;
    }

    //geters:

    int getPlayerNumber()
    {
        return player;
    }

    int getLifePoints()
    {
        return lifePoints;
    }

    int getFoolLifePoints()
    {
        return foolLife;
    }

    int getDamagePerActivity()
    {
        return damagePerActivity;
    }

    bool isAlive()
    {
        return ((lifePoints > 0) ? true : false);
    }

    virtual void activity(std::vector<std::vector<Soldier *>> &board, std::pair<int, int> position) = 0;
};

#endif