#include "Collider.h"


Collider::Collider(sf::Vector2f tam, sf::Vector2f pos, int t)
{
    col = sf::RectangleShape(tam);
    col.setPosition(pos);
    if(t == 0)
        col.setFillColor(sf::Color::Blue);
    if(t == 1)
        col.setFillColor(sf::Color::Red);

    tipo = t;



}

Collider::~Collider()
{
    //dtor
}

void Collider::update(Player &p, Enemy &e)
{
    if(tipo == 0) // si es el suelo
    {
        if(p.boundsRight().intersects(col.getGlobalBounds())) {
            p.setCol("right", true);
            p.setCanDestroy(false);

        } else if(p.boundsLeft().intersects(col.getGlobalBounds())) {
            p.setCol("left", true);
            p.setCanDestroy(false);


        } else if(p.boundsDown().intersects(col.getGlobalBounds())) {
            p.setCol("down", true);
            p.setCanDestroy(false);


        } else if(p.boundsUp().intersects(col.getGlobalBounds())) {
            p.setCol("up", true);
            p.setCanDestroy(false);

        }

        if(e.boundsLeft().intersects(col.getGlobalBounds())){
            e.setCol("left", true);

        } else if(e.boundsRight().intersects(col.getGlobalBounds())) {
            e.setCol("right", true);
        }
    }
    else if (tipo == 1) // si es una escalera
    {

        if(p.boundsUp().intersects(col.getGlobalBounds()) ||
           p.boundsDown().intersects(col.getGlobalBounds()) ||
           p.boundsRight().intersects(col.getGlobalBounds()) ||
           p.boundsLeft().intersects(col.getGlobalBounds()) )
           {
                if(!p.getIsOnAir()) {
                    p.setCol("stairs", true);
                }

           }
    }
}


void Collider::draw(sf::RenderWindow &window)
{
    window.draw(col);
}
