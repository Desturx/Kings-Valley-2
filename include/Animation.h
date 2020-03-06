#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Animation
{
    public:
        Animation();
        virtual ~Animation();

        void update(sf::Vector2f movement, float mTime);
        void draw(sf::RenderWindow &window);

        void setAnimation(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento, float duracion);
        void noLoop();
        void doLoop();

        bool animFinished();

        void setPosition(sf::Vector2f pos);
        void play();
        void stop();
        void flip(char direction);
        int getDir();
        void setOrigin(float x, float y);





    private:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::IntRect firstF;
        sf::IntRect finalF;
        sf::IntRect actualFrame;
        int incremento;
        float switchTime;
        sf::Clock clock;

        bool isPlaying;
        int dirSprite;
        bool loop;
        bool finished;


};

#endif // ANIMATION_H
