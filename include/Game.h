#pragma once
#include <iostream>
#include "Board.h"
class Game
{
private:
    Board& gameBoard;

    sf::Vector2i selectedSquare;
public:
    Game(Board& _gameBoard) : gameBoard(_gameBoard) {}

    void swapSquares(sf::Vector2i firstPosition, sf::Vector2i secondPosition);

    void handleMouseClick(sf::Vector2i position);

    bool checkCombinations();

    void update();
    void destroy();
    void addSquares();
    void shiftDown();
    void dropBonus(sf::Vector2i position);
    sf::Vector2i getNonNeighbor(sf::Vector2i position);
};