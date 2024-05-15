#include <SFML/Graphics.hpp> 
#include "Board.h"
#include "Game.h"
#include "Constants.h"
int main()
{


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GEMS Game");

    Board gameBoard(ROWS, COLS);
    Game game(gameBoard);
    std::cout << "Ff";
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2i position(mousePosition.x / (WINDOW_WIDTH / COLS), mousePosition.y / (WINDOW_HEIGHT / ROWS));

                    game.handleMouseClick(position);
                }
            }
        }
        game.update();

        window.clear(sf::Color::Black);

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                sf::RectangleShape square(sf::Vector2f(WINDOW_WIDTH / COLS, WINDOW_HEIGHT / ROWS));
                square.setPosition(i * (WINDOW_WIDTH / COLS), j * (WINDOW_HEIGHT / ROWS));
                square.setFillColor(gameBoard.getSquare(sf::Vector2i(i, j)).getColor());
                window.draw(square);
            }
        }

        window.display();
    }

    return 0;
}