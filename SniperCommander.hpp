#ifndef _SniperCommander_H
#define _SniperCommander_H

#include "Sniper.hpp"

class SniperCommander : public Sniper
{

private:
    int lifePoints = 120;
    int damagePerActivity = 100;

public:
    SniperCommander(int player, int lifePoints = 120, int damagePerActivity = 100)
        : Sniper(player, lifePoints, damagePerActivity)
    {
        std::cout << "sniper constructor" << std::endl;
    }

    ~SniperCommander() {}

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

        for (auto i = 0; i < board.size(); i++)
        {
            for (auto j = 0; j < board[i].size(); j++)
            {
                Soldier *sniperSoldier = board[i][j];

                if (sniperSoldier != nullptr && sniperSoldier->getPlayerNumber() == player)
                {
                    if (dynamic_cast<Sniper *>(sniperSoldier) && !dynamic_cast<SniperCommander *>(sniperSoldier))
                    {
                        sniperSoldier->activity(board, {i, j});
                    }
                }
            }
        }
    }
};

#endif