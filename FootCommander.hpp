
#ifndef _footCommender_H
#define _footCommender_H

#include "FootSoldier.hpp"

class FootCommander : public FootSoldier
{

private:
    int lifePoints = 150;
    int damagePerActivity = 20;

public:
    //constructor
    FootCommander(int player, int lifePoints = 150, int damagePerActivity = 20)
        : FootSoldier(player, lifePoints, damagePerActivity)
    {
        std::cout << "FootCommander constructor" << std::endl;
    }

    ~FootCommander() {}

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

                if (soldier != nullptr && soldier->getPlayerNumber() != player)
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

        for (auto i = 0; i < board.size(); i++)
        {
            for (auto j = 0; j < board[i].size(); j++)
            {
                Soldier *footSoldier = board[i][j];

                if (footSoldier != nullptr && footSoldier->getPlayerNumber() == player)
                {
                    if (dynamic_cast<FootSoldier *>(footSoldier) && !dynamic_cast<FootCommander *>(footSoldier))
                    {
                        footSoldier->activity(board, {i, j});
                    }
                }
            }
        }
    }
};

#endif