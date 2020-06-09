#ifndef _Sniper_H
#define _Sniper_H

#include "Soldier.hpp"

class Sniper : public Soldier
{

private:
    int lifePoints = 100;
    int damagePerActivity = 50;

public:
    Sniper(int player, int lifePoints = 100, int damagePerActivity = 50)
        : Soldier(player, lifePoints, damagePerActivity)
    {
        std::cout << "sniper constructor" << std::endl;
    }

    ~Sniper() {}

    void activity(std::vector<std::vector<Soldier *>> &board, std::pair<int, int> position) override
    {
        Soldier *strongestSoldier = nullptr;
        Soldier *soldier = nullptr;
        int ifStrongest = 0;

        for (size_t i = 0; i < board.size(); i++)
        {
            for (size_t j = 0; j < board[i].size(); j++)
            {
                soldier = board[i][j];

                if (soldier != nullptr && soldier->getPlayerNumber() != player)
                {
                    if (soldier->getLifePoints() > ifStrongest)
                    {
                        strongestSoldier = soldier;
                        ifStrongest = soldier->getLifePoints();
                    }
                }
            }
        }
        if (strongestSoldier)
            strongestSoldier->setLifePoints(strongestSoldier->getLifePoints() - damagePerActivity);
    }
};

#endif