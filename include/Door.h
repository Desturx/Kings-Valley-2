#ifndef DOOR_H
#define DOOR_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Door
{
    public:
        Door(sf::Vector2f pos);
        virtual ~Door();
        bool update(Player &p);

        void draw(sf::RenderWindow &window);

    private:
        sf::Texture texture;
        sf::Sprite sprite;

        bool anim;

        sf::RectangleShape hitbox;

        Animation* actual;
        Animation opening;

};

#endif // DOOR_H
