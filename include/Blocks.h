#ifndef BLOCKS_H
#define BLOCKS_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Animation.h"

class Blocks
{
    public:
        Blocks(sf::Vector2f tam, sf::Vector2f pos);
        virtual ~Blocks();

        void update(Player &p);
        void changeAnimation(Animation* newAnimation);
        void draw(sf::RenderWindow &window);
        bool isDestroyed();

    private:
        sf::Sprite sprite;
        sf::Texture texture;

        sf::RectangleShape hitbox;

        bool destroyed;

        Animation *actual;
        Animation breaking;
        Animation normal;
};

#endif // BLOCKS_H
