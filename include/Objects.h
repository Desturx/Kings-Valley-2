#ifndef OBJECTS_H
#define OBJECTS_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Objects
{
    public:
        Objects(sf::Vector2f pos);
        virtual ~Objects();

        bool update(Player &p);
        void draw(sf::RenderWindow &window);

    private:
        sf::CircleShape hitbox;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // OBJECTS_H
