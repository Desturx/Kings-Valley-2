#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"


class Enemy
{
    public:
        Enemy(sf::Vector2f pos);
        virtual ~Enemy();

        void moveColliders(float delta);

        void update(float delta, Player* &p);

        void setCol(std::string col, bool val);

        void drawColliders(sf::RenderWindow& window);
        void draw(sf::RenderWindow &window);

        sf::FloatRect getGlobalBounds();
        sf::FloatRect boundsRight();
        sf::FloatRect boundsLeft();

    private:
        sf::Vector2f movement;

        float speed;
        int dirMov;
        float grav;

        sf::RectangleShape hitbox;

        // colisionadores
        sf::RectangleShape c_izq;
        sf::RectangleShape c_der;
        sf::RectangleShape c_abj;
        sf::RectangleShape c_arr;

        bool down, left, right;

        sf::Clock before;

        Animation *actual;
        Animation run;
        Animation idle;

};

#endif // ENEMY_H
