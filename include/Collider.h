#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Enemy.h"

class Collider
{
    public:
        Collider(sf::Vector2f tam, sf::Vector2f pos, int tip);
        virtual ~Collider();

        // Update
        void update(Player &p, Enemy &e);

        //Draw
        void draw(sf::RenderWindow &window);

    private:
        sf::RectangleShape col;
        int tipo;

};

#endif // COLLIDER_H
