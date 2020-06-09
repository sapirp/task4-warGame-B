#include "Board.hpp"

using namespace std;

Soldier *&WarGame::Board::operator[](std::pair<int, int> location)
{
    return board[location.first][location.second];
}

Soldier *WarGame::Board::operator[](std::pair<int, int> location) const
{
    return board[location.first][location.second];
}

void WarGame::Board::move(uint player_number, std::pair<int, int> source, WarGame::Board::MoveDIR direction)
{
    Soldier *soldier = board.at(source.first).at(source.second);
    // check if there is no soldier in the source location
    if (!soldier)
    {
        throw std::invalid_argument("There is no soldier in the source location");
    }
    // check if the soldier in the source location don`t belong to this player
    if (soldier->getPlayerNumber() != player_number)
    {
        throw std::invalid_argument("The soldier in the source location belongs to the other player");
    }
    //set the new location
    std::pair<int, int> newLocation;
    switch (direction)
    {
    case MoveDIR::Up:
        newLocation = {source.first + 1, source.second};
        break;
    case MoveDIR::Down:
        newLocation = {source.first - 1, source.second};
        break;
    case MoveDIR::Left:
        newLocation = {source.first, source.second - 1};
        break;
    case MoveDIR::Right:
        newLocation = {source.first, source.second + 1};
        break;
    default:
        break;
    }
    //check if ther is allready a soldier in the new location.
    Soldier *checkSoldier = board.at(newLocation.first).at(newLocation.second);
    if (checkSoldier)
    {
        throw std::invalid_argument("There is already another soldier in the target location");
    }

    board[source.first][source.second] = nullptr;
    board[newLocation.first][newLocation.second] = soldier;

    soldier->activity(board, newLocation);
    this->lookForDeads();
}

bool WarGame::Board::has_soldiers(uint player_number) const
{
    Soldier *player_chack;
    for (auto i = 0; i < board.size(); i++)
    {
        for (auto j = 0; j < board[i].size(); j++)
        {
            cout << board[i][j] << " ";
            player_chack = board[i][j];
            if (player_chack && (*player_chack).getPlayerNumber() == player_number)
                return true;
        }
        cout << endl;
    }
    return false;
}

float WarGame::Board::dist(const std::pair<int, int> &source, const std::pair<int, int> &soldierLocation)
{
    return sqrt(pow(soldierLocation.first - source.first, 2) +
                pow(soldierLocation.second - source.second, 2) * 1.0);
}

void WarGame::Board::lookForDeads()
{
    for (auto i = 0; i < board.size(); i++)
    {
        for (auto j = 0; j < board[i].size(); j++)
        {
            Soldier *soldier = board[i][j];
            if (soldier && !(soldier->isAlive()))
            {
                board[i][j] = nullptr;
            }
        }
    }
}
