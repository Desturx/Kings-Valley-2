#ifndef GAME_H
#define GAME_H

#define updateTimePS 1000/30  // Sería un update de 30 veces por segundo.


#include "Player.h"
#include "Map.h"
#include "Objects.h"
#include "Door.h"
#include "Tool.h"
#include "Enemy.h"



class Game
{
    public:
        Game();
        virtual ~Game();
        void start();
        void initializer();
        void events();
        void updateGame(float elapsedTime);
        void render();


    private:
        sf::RenderWindow gameWindow;

        // clocks
        sf::Clock updatesPS; // controla la velocidad del update del juego
        sf::Clock gameUpdate; // controla el update del juego
        sf::Time timesUpdate;

        // Event
        sf::Event event;

        //View
        sf::View view;

        // objects
        Player *pj;
        Enemy *en;
        Map *currentMap;
        Door *door;
        std::vector<Tool*> tools;
        sf::Sprite ataud;
        sf::Texture textureAtaud;
        bool endgame;



};

#endif // GAME_H
