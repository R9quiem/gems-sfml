#include "Board.h"

Board::Board(int _rows, int _cols) : rows(_rows), cols(_cols) {
    for (int i = 0; i < rows; ++i) {
        std::vector<Square> row;
        for (int j = 0; j < cols; ++j) {
            sf::Color color = getRandomColor();
            sf::Vector2i position(i, j);
            row.push_back(Square(color, position));
        }
        board.push_back(row);
    }
}
sf::Color Board::getRandomColor() const {
    switch (std::rand() % 5) {
    case 0: return sf::Color::Red;
    case 1: return sf::Color::Green;
    case 2: return sf::Color::Blue;
    case 3: return sf::Color::Yellow;
    case 4: return sf::Color::Magenta;
    default: return sf::Color::White;
    }
}