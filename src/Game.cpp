#include "Game.h"


Game::Game()
{
    gameWindow.create(sf::VideoMode(800, 720), "Kings Valley 2");

    view.zoom(1.05f);


}

Game::~Game()
{
    //dtor
}

void Game::start()
{


    initializer();

    while(gameWindow.isOpen()){

        events();

        if(updatesPS.getElapsedTime().asMilliseconds() - timesUpdate.asMilliseconds() > updateTimePS ){
            updateGame(gameUpdate.restart().asMilliseconds()); //Bucle de juego
            timesUpdate = updatesPS.getElapsedTime();
        }

        render();
    }

}


void Game::initializer()
{

    timesUpdate = updatesPS.getElapsedTime();

    // Los objetos y personaje
//    pj = new Player(sf::Vector2f(571, 437));
    pj = new Player(sf::Vector2f(571, 630));
    en = new Enemy(sf::Vector2f(200, 150));

    currentMap = new Map(1);
    door = new Door(sf::Vector2f(416, 64));


    // herramientas del mapa
    Tool* pickaxe = new Tool(0, sf::Vector2f(224, 320));
    Tool* drill = new Tool(1, sf::Vector2f(736, 320));

    tools.push_back(pickaxe);
    tools.push_back(drill);

    if(!textureAtaud.loadFromFile("resources/sprites/ataud.png")) {
        std::cout << "ERROR EN LA CARGA" << std::endl;
    }
    ataud.setTexture(textureAtaud);

    ataud.setPosition(150, 97);


    view.setCenter(510, 400);
    endgame = false;

}

void Game::events()
{
    while (gameWindow.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
            gameWindow.close();
        if (event.key.code == sf::Keyboard::Escape)
            gameWindow.close();
        if (event.key.code == sf::Keyboard::N) {
            timesUpdate = updatesPS.getElapsedTime();
            // Los objetos y personaje
            pj = new Player(sf::Vector2f(571, 437));
            currentMap = new Map(2);
            view.setCenter(510, 400);
        }
    }
}


void Game::updateGame(float elapsedTime)
{
    // Update del jugador
    pj->update(elapsedTime);

    if(pj->getGameOver()) {
        initializer();
    }

    // Update del enemigo
    en->update(elapsedTime, pj);
    // Update del mapa
    currentMap->update(pj, en);

    // Update de la puerta
    if(door->update(*pj)) {
//        std::cout << "HA TERMINADO LA PARTIDA" << std::endl;
        endgame = true;
    }

    // Update de las armas
    for(int i = 0; i < tools.size(); i++) {
        if(tools.at(i)->update(pj)) {
            delete tools.at(i);
            tools.erase(tools.begin()+i);
        }
    }


    // PARA TERMINAR LA PARTIDA;
    if(endgame) {
        std::cout << "entra en endgame" << std::endl;
        endgame = false;
        timesUpdate = updatesPS.getElapsedTime();
        // Los objetos y personaje
        pj = new Player(sf::Vector2f(571, 437));
        currentMap = new Map(2);
        door = new Door(sf::Vector2f(416, 64));

        view.setCenter(510, 400);
    }
}

void Game::render()
{
    gameWindow.clear();
    gameWindow.setView(view);
    currentMap->draw(gameWindow);
    door->draw(gameWindow);

    for(int i = 0; i < tools.size(); i++){
        tools.at(i)->draw(gameWindow);
    }
    gameWindow.draw(ataud);
    pj->draw(gameWindow);
    en->draw(gameWindow);

    gameWindow.display();
}
