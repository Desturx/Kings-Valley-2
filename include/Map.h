#ifndef MAP_H
#define MAP_H


#include "tinyxml2.h"
#include <iostream>;
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Objects.h"
#include "Blocks.h"


using namespace std;
using namespace sf;
using namespace tinyxml2;


class Map
{
    public:
        Map(int lvl);
        virtual ~Map();
        void readMap(int nivel);
        void setData();
        void loadTextures();
        void createSprites();
        void getLayers();
        void creaColisiones();

        void printData();


        void update(Player* &p, Enemy* &e);
        void draw(RenderWindow& target);

    private:
        int width, height;
        int tileWidth, tileHeight;
        int gid;

        XMLDocument docum;
        XMLElement* xmlMap;
        XMLElement* tileSetImg;
        XMLElement* data;
        XMLElement* layer;

        string ficheroImagen;
        Texture tileSetTexture;

        int numLayers = 0;
        int*** tileMap;

        Sprite* tilesetSprite;
        Sprite**** mapSprite;


        std::vector<Collider> colisiones;
        std::vector<Objects*> esferas;
        std::vector<Blocks*> destrBlocks;
};


#endif // MAP_H
