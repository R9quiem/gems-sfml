#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
class Square {
private:
    sf::Color color;
    sf::Vector2i position;

public:
    Square(sf::Color _color, sf::Vector2i _position) : color(_color), position(_position) {}

    // Ãåòòåðû
    sf::Color getColor() const { return color; }
    sf::Vector2i getPosition() const { return position; }

    // Ñåòòåðû
    void setColor(sf::Color _color) { color = _color; }
    void setPosition(sf::Vector2i _position) { position = _position; }
    
};