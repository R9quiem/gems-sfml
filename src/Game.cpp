#include "Game.h"
#include "Constants.h"
#include <SFML/System.hpp>
void Game::handleMouseClick(sf::Vector2i position) {
    // Çäåñü áóäåò ëîãèêà îáðàáîòêè êëèêîâ ìûøè
    if (selectedSquare.x != -1) {
        // Åñëè ýòî íå ïåðâûé êëèê, ïûòàåìñÿ ïîìåíÿòü âûáðàííûé êâàäðàò ñ ñîñåäíèì

        if (std::abs(selectedSquare.x - position.x) + std::abs(selectedSquare.y - position.y) == 1) {
            // Åñëè ýòî íå ïåðâûé êëèê, ïûòàåìñÿ ïîìåíÿòü âûáðàííûé êâàäðàò ñ ñîñåäíèì
            swapSquares(selectedSquare, position);
        }
        // Ïîñëå îáìåíà ñáðàñûâàåì âûáðàííûé êâàäðàò
        selectedSquare = sf::Vector2i(-1, -1);
    } else {
        // Åñëè ýòî ïåðâûé êëèê, ïðîñòî âûáèðàåì êâàäðàò
        selectedSquare = position;
    }
}

void Game::update() {
    // Ïðîâåðÿåì íàëè÷èå êîìáèíàöèé
    bool combinationsFound = checkCombinations();

    // Åñëè åñòü êîìáèíàöèè, îáíîâëÿåì èãðîâîå ïîëå
    if (combinationsFound) {
        destroy();

    }
    shiftDown();
    addSquares();
}

void Game::dropBonus(sf::Vector2i position) {
    int bonusType = rand() % 2; // 0 - Ïåðåêðàøèâàíèå, 1 - Áîìáà

    if (bonusType == 0) {
        // Ïåðåêðàøèâàíèå
        // Ïîëó÷àåì ñëó÷àéíûé öâåò
        sf::Color newColor = gameBoard.getRandomColor();

        // Ïåðåêðàøèâàåì êâàäðàò, êóäà ïîïàë áîíóñ
        gameBoard.getSquare(position).setColor(newColor);

        // Âûáèðàåì äâà ñëó÷àéíûõ íåïîñðåäñòâåííûõ ñîñåäà êâàäðàòà, ÷òîáû íå ìåíÿòü ñîñåäíèå öâåòà
        sf::Vector2i neighbor1 = getNonNeighbor(position);
        sf::Vector2i neighbor2 = getNonNeighbor(position);

        // Ïåðåêðàøèâàåì âûáðàííûå êâàäðàòû
        gameBoard.getSquare(neighbor1).setColor(newColor);
        gameBoard.getSquare(neighbor2).setColor(newColor);
    }
    else {
        // Áîìáà
        // Óíè÷òîæàåì 5 ñëó÷àéíûõ êâàäðàòîâ íà ïîëå, âêëþ÷àÿ òîò, êóäà ïîïàë áîíóñ
        for (int i = 0; i < 4; ++i) {
            int x = rand() % COLS;
            int y = rand() % ROWS;
            gameBoard.getSquare(sf::Vector2i(x, y)).setColor(sf::Color::White);
        }
        gameBoard.getSquare(position).setColor(sf::Color::White);
    }
}
sf::Vector2i Game::getNonNeighbor(sf::Vector2i position) {
    // Ïîëó÷àåì ñëó÷àéíîãî ñîñåäà êâàäðàòà position
    int dx = rand() % 3 - 1; // Ñëó÷àéíîå ñìåùåíèå ïî x: -1, 0 èëè 1
    int dy = rand() % 3 - 1; // Ñëó÷àéíîå ñìåùåíèå ïî y: -1, 0 èëè 1

    // Óáåæäàåìñÿ, ÷òî ñìåùåíèå íå ïðèâîäèò ê âûõîäó çà ãðàíèöû ïîëÿ è íå ÿâëÿåòñÿ ñîñåäíèì ê position
    while ((dx == 0 && dy == 0) ||
        (position.x + dx < 0 || position.x + dx >= COLS) ||
        (position.y + dy < 0 || position.y + dy >= ROWS)) {
        dx = rand() % 3 - 1;
        dy = rand() % 3 - 1;
    }

    return sf::Vector2i(position.x + dx, position.y + dy);
}
void Game::shiftDown() {
    // Ñäâèãàåì êâàäðàòû âíèç
    for (int i = 0; i < COLS; ++i) {
        
        for (int j = 0; j < ROWS-1; ++j) {
            if (gameBoard.getSquare(sf::Vector2i(i, j)).getColor() != sf::Color::White &&
               gameBoard.getSquare(sf::Vector2i(i, j+1)).getColor() == sf::Color::White) {
                // Ñäâèãàåì òåêóùèé êâàäðàò âíèç
                int row = j;
                while (row + 1 < ROWS && gameBoard.getSquare(sf::Vector2i(i, row + 1)).getColor() == sf::Color::White) {
                    swapSquares(sf::Vector2i(i, row), sf::Vector2i(i, row + 1));
                    ++row;
                }
            }
        }
    }
}
void Game::addSquares() {
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS - 1; ++j) {
            Square &square = gameBoard.getSquare(sf::Vector2i(i, j));
            if (square.getColor() == sf::Color::White) {
                square.setColor(gameBoard.getRandomColor());
            }
        }
    }
}
void Game::swapSquares(sf::Vector2i firstPosition, sf::Vector2i secondPosition) {
    Square& firstSquare = gameBoard.getSquare(firstPosition);
    Square& secondSquare = gameBoard.getSquare(secondPosition);
    sf::Color tempColor = firstSquare.getColor();

    firstSquare.setColor(secondSquare.getColor());
    secondSquare.setColor(tempColor);
}

bool Game::checkCombinations() {
    // Ïðîõîäèì ïî âñåì êâàäðàòàì íà èãðîâîì ïîëå
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            sf::Color color = gameBoard.getSquare(sf::Vector2i(i, j)).getColor();

            // Ïðîâåðÿåì ãîðèçîíòàëüíûå êîìáèíàöèè
            int horizontalCount = 1;
            for (int k = j + 1; k < COLS; ++k) {
                if (gameBoard.getSquare(sf::Vector2i(i, k)).getColor() == color) {
                    horizontalCount++;
                }
                else {
                    break;
                }
            }
            if (horizontalCount >= 3) {
                return true; 
            }

            int verticalCount = 1;
            for (int k = i + 1; k < ROWS; ++k) {
                if (gameBoard.getSquare(sf::Vector2i(k, j)).getColor() == color) {
                    verticalCount++;
                }
                else {
                    break;
                }
            }
            if (verticalCount >= 3) {
                return true;
            }
        }
    }

    return false; 
}

void Game::destroy() {

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            sf::Color color = gameBoard.getSquare(sf::Vector2i(i, j)).getColor();

            int horizontalCount = 1;
            int k = j + 1;
            while (k < COLS && gameBoard.getSquare(sf::Vector2i(i, k)).getColor() == color) {
                horizontalCount++;
                k++;
            }

            int verticalCount = 1;
            int l = i + 1;
            while (l < ROWS && gameBoard.getSquare(sf::Vector2i(l, j)).getColor() == color) {
                verticalCount++;
                l++;
            }

            if (horizontalCount >= 3) {
                for (int m = j; m < j + horizontalCount; ++m) {
                    gameBoard.getSquare(sf::Vector2i(i, m)).setColor(sf::Color::White);
                }
                if (rand() % 4 == 0) {
                    dropBonus(sf::Vector2i(i, j));
                }
            }
            if (verticalCount >= 3) {
                for (int n = i; n < i + verticalCount; ++n) {
                    gameBoard.getSquare(sf::Vector2i(n, j)).setColor(sf::Color::White);
                }
                if (rand() % 4 == 0) {
                    dropBonus(sf::Vector2i(i, j));
                }
            }
        }
    }
}