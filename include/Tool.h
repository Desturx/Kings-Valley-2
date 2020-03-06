#ifndef TOOL_H
#define TOOL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"


class Tool
{
    public:
        Tool(int t, sf::Vector2f pos);
        virtual ~Tool();
        bool update(Player* &p);
        void draw(sf::RenderWindow &window);


    private:
        int tipo;
        sf::Texture texture;
        sf::Sprite sprite;

        sf::RectangleShape hitbox;
};

#endif // TOOL_H
