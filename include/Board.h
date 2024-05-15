#pragma once
#include <vector>
#include "Square.h"

class Board
{
private:
    std::vector<std::vector<Square>> board;
    int rows;
    int cols;

public:
    Board(int _rows, int _cols);

    // Ãåíåðàöèÿ ñëó÷àéíîãî öâåòà
    sf::Color getRandomColor() const;

    // Ïîëó÷åíèå êâàäðàòà ïî ïîçèöèè
    Square& getSquare(sf::Vector2i position) { return board[position.x][position.y]; }
};