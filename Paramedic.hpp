#ifndef _Paramedic_H
#define _Paramedic_H

#include "Soldier.hpp"

class Paramedic : public Soldier
{

private:
    int lifePoints = 100;
    int damagePerActivity = 0;

public:
    Paramedic(int player, int lifePoints = 100, int damagePerActivity = 0)
        : Soldier(player, lifePoints, damagePerActivity)
    {
        std::cout << "paramedic constructor" << std::endl;
    }

    ~Paramedic() {}

    void activity(std::vector<std::vector<Soldier *>> &board, std::pair<int, int> position) override
    {
        Soldier *closestSoldier = nullptr;

        for (auto i = std::max(0, position.first - 1); i < std::min(static_cast<int>(board.size()), position.first + 1); i++)
        {
            for (auto j = std::max(0, position.second - 1); j < std::min(static_cast<int>(board[i].size()), position.second + 1); j++)
            {
                Soldier *soldier = board[i][j];
                std::pair<int, int> currnetPosition(i, j);
                if (soldier && soldier->getPlayerNumber() == player && position != currnetPosition)
                {
                    soldier->setLifePoints(soldier->getFoolLifePoints());
                }
            }
        }
    }
};

#endif