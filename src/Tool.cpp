#include "Tool.h"

Tool::Tool(int t, sf::Vector2f pos)
{
    hitbox = sf::RectangleShape(sf::Vector2f(32,32));

    if(t == 0) // es un pico
    {
        hitbox.setPosition(pos);
        texture.loadFromFile("resources/sprites/pico.png");
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        tipo = 0;

    }
    else if(t == 1) // es una taladradora
    {
        hitbox.setPosition(pos.x+20, pos.y);
        texture.loadFromFile("resources/sprites/taladro.png");
        sprite.setTexture(texture);
        sprite.setPosition(pos);
        tipo = 1;


    }
    else
    {
        std::cout << "NO EXISTE ESE ARMA" << std::endl;
    }
}

Tool::~Tool()
{
    //dtor
}


bool Tool::update(Player* &p)
{
    bool res = false;

    if(p->getGlobalBounds().intersects(hitbox.getGlobalBounds())) {
        p->setTool(tipo);
        res = true;
    }

    return res;
}

void Tool::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
