#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include <iostream>

class Player
{
    public:
        Player(sf::Vector2f pos);
        virtual ~Player();

        void update(float delta);
        void draw(sf::RenderWindow &window);
        void drawColliders(sf::RenderWindow& window);
        void setCol(std::string col, bool val);

        void jumping(float delta);
        void moving(float delta);
        void moveColliders(float delta);
        void changeAnimation(Animation* newAnimation);
        void controlPosition();
        void setSpheres();

        void resume();
        void stop();

        void dontDraw();
        void doDraw();

        void setTool(int t);
        void setCanDestroy(bool val);



        sf::FloatRect getGlobalBounds();
        sf::FloatRect boundsDown();
        sf::FloatRect boundsUp();
        sf::FloatRect boundsRight();
        sf::FloatRect boundsLeft();

        bool getIsOnAir();
        bool getDestrBloque();
        int getSpheres();
        int getTool();
        bool getGameOver();

        void kill();





    private:
        sf::RectangleShape hitbox;

        sf::Vector2f movement;
        sf::Vector2f pCenter;
        float speed;
        int dirMov;

        float grav;

        int sph_collected = 0;


        // colisionadores
        sf::RectangleShape c_izq;
        sf::RectangleShape c_der;
        sf::RectangleShape c_abj;
        sf::RectangleShape c_arr;

        bool up, down, left, right, stairs, isJumping, isOnAir;


        bool destrBloque;
        bool stopped = false;
        bool drawing = true;
        bool canDestroy;

        bool godMode;
        sf::Clock cdGod;

        int currentTool;

        bool gameOver;
        bool restartLevel;

        sf::Clock cdArma;
        sf::Clock deadTime;
        sf::Clock groundTime;

        // Animaciones del jugador;
        Animation* actual;

        Animation run;
        Animation climb;
        Animation jump;

        Animation s_run;
        Animation s_climb;
        Animation s_use;

        Animation p_run;
        Animation p_climb;
        Animation p_use;

        Animation d_run;
        Animation d_climb;
        Animation d_use;

        Animation dying;
        Animation dead;

};

#endif // PLAYER_H
