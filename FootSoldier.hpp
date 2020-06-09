
#ifndef _footSoldier_H
#define _footSoldier_H

#include <float.h>
#include "Soldier.hpp"

using namespace WarGame;

class FootSoldier : public Soldier
{
private:
    int lifePoints = 100;
    int damagePerActivity = 10;

public:
    //constructor
    FootSoldier(int player, int lifePoints = 100, int damagePerActivity = 10)
        : Soldier(player, lifePoints, damagePerActivity)
    {
        std::cout << "FootSoldier constructor" << std::endl;
    }

    ~FootSoldier() {}

    void activity(std::vector<std::vector<Soldier *>> &board, std::pair<int, int> position) override
    {
        Soldier *soldier = nullptr;
        Soldier *closestSoldier = nullptr;
        float oldDist = SIZE_MAX;
        float newDist = 0;

        for (auto i = 0; i < board.size(); i++)
        {
            for (auto j = 0; j < board[i].size(); j++)
            {
                soldier = board[i][j];

                if (soldier != nullptr && soldier->isAlive() && soldier->getPlayerNumber() != player)
                {
                    newDist = Board::dist({i, j}, position);
                    if (newDist < oldDist)
                    {
                        closestSoldier = soldier;
                        oldDist = newDist;
                    }
                }
            }
        }
        if (closestSoldier)
            closestSoldier->setLifePoints(closestSoldier->getLifePoints() - damagePerActivity);
    }
};

#endif