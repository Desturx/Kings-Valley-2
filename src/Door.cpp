#include "Door.h"

Door::Door(sf::Vector2f pos)
{
    hitbox = sf::RectangleShape(sf::Vector2f(128, 128));
    hitbox.setPosition(pos);
    hitbox.setFillColor(sf::Color::Yellow);

    texture.loadFromFile("resources/maps/closed_door/closed_door1.png");
    sprite.setTexture(texture);
    sprite.setPosition(pos);

    opening.setAnimation("resources/maps/pAbierta.png", sf::IntRect(0, 0, 128, 128), sf::IntRect(128*9, 0, 128, 128), 128, 0.15f);
    actual = &opening;
    actual->setPosition(hitbox.getPosition());
    actual->setOrigin(0.f, 0.f);
    actual->noLoop();



    anim = false;


}

Door::~Door()
{
    //dtor
}

bool Door::update(Player &p)
{
    bool res = false;

    if(p.getSpheres() == 0)
    {
        texture.loadFromFile("resources/maps/closed_door/closed_door1.png");
    }
    else if(p.getSpheres() == 1)
    {
        texture.loadFromFile("resources/maps/closed_door/closed_door2.png");
    }
    else if(p.getSpheres() == 2)
    {
       texture.loadFromFile("resources/maps/closed_door/closed_door3.png");
    }
    else if(p.getSpheres() == 3)
    {
        texture.loadFromFile("resources/maps/closed_door/closed_door4.png");
    }
    else if(p.getSpheres() == 4)
    {
        texture.loadFromFile("resources/maps/closed_door/closed_door5.png");
    }
    sprite.setTexture(texture);
    sprite.setPosition(hitbox.getPosition());

    if(p.getGlobalBounds().intersects(hitbox.getGlobalBounds()) && p.getSpheres() == 4) {
        anim = true;
        actual->update(sf::Vector2f(0,0), 0);
        p.stop();
        p.dontDraw();
    }

    if(actual->animFinished()) {
        res = true;
    }

    return res;

}

void Door::draw(sf::RenderWindow &window)
{
    window.draw(hitbox);
    if(!anim)
        window.draw(sprite);
    else
        actual->draw(window);
}
