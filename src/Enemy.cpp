#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos)
{
    grav = 0.006f;
    movement = sf::Vector2f(.08f, 0.f);
    speed = .20f;

    hitbox = sf::RectangleShape(sf::Vector2f(64, 64));
    hitbox.setFillColor(sf::Color::Red);
    hitbox.setOrigin(64/2, 64/2);
    hitbox.setPosition(pos);

    left = false;
    right = false;


    idle.setAnimation("resources/sprites/momia.png", sf::IntRect(0,0, 64, 64), sf::IntRect(0, 0, 64, 64), 64, 0.15f);
    run.setAnimation("resources/sprites/momia.png", sf::IntRect(64,0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);
    actual = &run;
    actual->setPosition(hitbox.getPosition());

    c_izq = sf::RectangleShape(sf::Vector2f(3, 48));
    c_izq.setPosition(pos.x - 35, pos.y - 48/2);
    c_izq.setFillColor(sf::Color::Green);

    c_der = sf::RectangleShape(sf::Vector2f(3, 48));
    c_der.setPosition(pos.x + 35, pos.y - 48/2);
    c_der.setFillColor(sf::Color::Green);


    before.restart();
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::moveColliders(float delta)
{
    c_abj.move(delta*movement);
    c_arr.move(delta*movement);
    c_izq.move(delta*movement);
    c_der.move(delta*movement);
}
void Enemy::update(float delta, Player* &p)
{
//    movement = sf::Vector2f(0.f, 0.f);
    if(hitbox.getGlobalBounds().intersects(p->getGlobalBounds())) {
        p->kill();
    }


    if(hitbox.getPosition().y >= 649) {
        movement.y = 0;
        if(hitbox.getPosition().y != 660) {
            hitbox.setPosition(hitbox.getPosition().x, 660);
        }
        if(right) {
            movement.x -= 0.1f;
            left = false;
            if(actual != &run) {
                actual = &run;
                actual->setPosition(hitbox.getPosition());
            }
            actual->flip('l');
        }
        if(left) {
            movement.x += 0.1f;
            right = false;
            actual = &run;

            actual->flip('r');

        }

    } else {
        if(right) {
            movement.x = 0;
            movement.y += 0.008f;
            actual = &idle;
            actual->setPosition(hitbox.getPosition());
        }

    }

    moveColliders(delta);
    hitbox.move(movement*delta);
    actual->update(movement, delta);

    left = false;
    right = false;

}


void Enemy::setCol(std::string col, bool val)
{
    if(col.compare("down") == 0) {
        down = val;
    } else if(col.compare("right") == 0) {
        right = val;
    } else if(col.compare("left") == 0) {
        left = val;
    }
}

sf::FloatRect Enemy::boundsLeft()
{
    return c_izq.getGlobalBounds();
}

sf::FloatRect Enemy::boundsRight()
{
    return c_der.getGlobalBounds();
}


void Enemy::drawColliders(sf::RenderWindow &window)
{
    window.draw(c_izq);
    window.draw(c_der);
    window.draw(c_abj);
    window.draw(c_arr);
}

void Enemy::draw(sf::RenderWindow& window)
{
    actual->draw(window);
}


