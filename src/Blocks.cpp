#include "Blocks.h"


Blocks::Blocks(sf::Vector2f tam, sf::Vector2f pos)
{
    hitbox = sf::RectangleShape(tam);

    hitbox.setPosition(pos);

    // Animations
    normal.setAnimation("resources/maps/bloque-rompible.png",sf::IntRect(0,0, 64, 64), sf::IntRect(0, 0, 64, 64), 64, 0.15f);
    breaking.setAnimation("resources/maps/bloque-rompible.png",sf::IntRect(0,0, 64, 64), sf::IntRect(8*64, 0, 64, 64), 64, 0.15f);


    changeAnimation(&normal);
    actual->setOrigin(0.f, 0.f);


    destroyed = false;

}

Blocks::~Blocks()
{

}

void Blocks::changeAnimation(Animation* newAnimation) {
    actual = newAnimation;
//    std::cout << "origen: " << hitbox.getOrigin().x << ", "<< hitbox.getOrigin().y << std::endl;
//    std::cout << "position " << hitbox.getPosition().x << ", " << hitbox.getPosition().y << std::endl;
    actual->setPosition(hitbox.getPosition());
    actual->setOrigin(0.f, 0.f);
    actual->noLoop();

}


void Blocks::update(Player &p)
{

    if(p.getDestrBloque()){
        if(p.getTool() == 0)
        {
            if(p.boundsDown().intersects(hitbox.getGlobalBounds())) {
                changeAnimation(&breaking);
            }
        }
        else if(p.getTool() == 1)
        {
            if(p.boundsLeft().intersects(hitbox.getGlobalBounds())) {
                changeAnimation(&breaking);
            } else if(p.boundsRight().intersects(hitbox.getGlobalBounds())) {
                changeAnimation(&breaking);
            }
        }

    }
    else if(!p.getDestrBloque())
    {
        if(p.boundsRight().intersects(hitbox.getGlobalBounds())) {
            if(p.getTool() == 1) {
                p.setCanDestroy(true);
            }
            p.setCol("right", true);

        } else if(p.boundsLeft().intersects(hitbox.getGlobalBounds())) {
            if(p.getTool() == 1) {
                p.setCanDestroy(true);
            }
            p.setCol("left", true);

        } else if(p.boundsDown().intersects(hitbox.getGlobalBounds())) {
            if(p.getTool() == 0) {
                p.setCanDestroy(true);
            }
            p.setCol("down", true);

        } else if(p.boundsUp().intersects(hitbox.getGlobalBounds())) {
            p.setCol("up", true);
        }
    }

    actual->update(sf::Vector2f(0,0), 0);
    if(actual->animFinished() && actual != &normal) {
        destroyed = true;
//        std::cout << "animacion finalizada" << std::endl;
    }

}

bool Blocks::isDestroyed()
{
    return destroyed;
}


void Blocks::draw(sf::RenderWindow &window)
{

    actual->draw(window);

}
