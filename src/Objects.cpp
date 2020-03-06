#include "Objects.h"
#include <iostream>

Objects::Objects(sf::Vector2f pos)
{
    texture.loadFromFile("resources/sprites/bola.png");
    sprite.setTexture(texture);
    hitbox = sf::CircleShape(28);
    hitbox.setFillColor(sf::Color::Yellow);
    hitbox.setPosition(pos);
    sprite.setPosition(pos.x - 5, pos.y - 5);
}


Objects::~Objects()
{
    //dtor
}

bool Objects::update(Player &p)
{
    bool colisionan = false;

    if(p.getGlobalBounds().intersects(hitbox.getGlobalBounds())) {
//        std::cout << "COLISIONAN" << std::endl;
        colisionan = true;
    }

    return colisionan;

}


void Objects::draw(sf::RenderWindow &window)
{

    window.draw(sprite);

}
