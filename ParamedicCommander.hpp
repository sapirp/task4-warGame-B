#ifndef _ParamedicCommander_H
#define _ParamedicCommander_H

#include "Paramedic.hpp"

class ParamedicCommander : public Paramedic
{

private:
    int lifePoints = 200;
    int damagePerActivity = 0;

public:
    ParamedicCommander(int player, int lifePoints = 200, int damagePerActivity = 0)
        : Paramedic(player, lifePoints, damagePerActivity)
    {
        std::cout << "paramedic constructor" << std::endl;
    }

    ~ParamedicCommander() {}

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
        for (auto i = 0; i < board.size(); i++)
        {
            for (auto j = 0; j < board[i].size(); j++)
            {
                Soldier *paramedic = board[i][j];

                if (paramedic != nullptr && paramedic->getPlayerNumber() == player)
                {
                    if (dynamic_cast<Paramedic *>(paramedic) && !dynamic_cast<ParamedicCommander *>(paramedic))
                    {
                        paramedic->activity(board, {i, j});
                    }
                }
            }
        }
    }
};
#endif