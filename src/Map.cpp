#include "Map.h"

Map::Map(int lvl)
{
    if(lvl == 1) {
        readMap(1);
    } else if(lvl == 2) {
        readMap(2);
    } else {
        std::cout << "MAPA INCORRECTO" << std::endl;
    }
    setData();
    loadTextures();
    createSprites();
}

Map::~Map()
{
    //dtor

    for(int i = 0; i < numLayers; i++) {
        for(int j = 0; j < height; j++) {
            delete tileMap[i][j];
        }
        delete tileMap[i];
    }
    delete tileMap;

    for(int i = 0; i < numLayers; i++) {
        for(int j = 0; j = height; j++) {
            for(int z = 0; z < width; z++) {
                delete mapSprite[i][j][z];
            }
            delete mapSprite[i][j];
        }
        delete mapSprite[i];
    }
    delete mapSprite;
    colisiones.clear();


}

void Map::readMap(int lvl)
{
    if(lvl == 1) {
        docum.LoadFile("resources/maps/mapajuego.tmx");
    }
    if(lvl == 2) {
        docum.LoadFile("resources/maps/mapajuego2.tmx");

    }


    xmlMap = docum.FirstChildElement("map");
}

void Map::setData()
{
    // Saco los datos del XML y los almaceno
    xmlMap->QueryIntAttribute("width", &width);
    xmlMap->QueryIntAttribute("height", &height);
    xmlMap->QueryIntAttribute("tilewidth", &tileWidth);
    xmlMap->QueryIntAttribute("tileheight", &tileHeight);

    tileSetImg = xmlMap->FirstChildElement("tileset");

    layer = xmlMap->FirstChildElement("layer");
}



void Map::loadTextures()
{
    while(tileSetImg) {
        // en un principio dentro de loadFrom file va la ruta que saco del tile, o sea "ficheroImagen"
        if(!tileSetTexture.loadFromFile("resources/maps/bloques2.png")){
            std::cerr << "No se ha podido cargar la textura" << std::endl;
            exit(0);
        }
        tileSetImg = tileSetImg->NextSiblingElement("tileset");
    }

    //saco el número de capas
    getLayers();
//    std::cout << "NUM CAPAS : " << numLayers << std::endl;

    layer = xmlMap->FirstChildElement("layer"); //Volvemos a la primera capa

    // carga de varios objetos
    creaColisiones();


    // DEVOLVER EL LAYER A LA POSICION QUE LE TOCA
    layer = xmlMap->FirstChildElement("layer"); //Volvemos a la primera capa


    tileMap = new int**[numLayers];


    // Declarar las capas
    for(int i = 0; i < numLayers; i++) {
        tileMap[i] = new int*[height]; // alto del tilemap
        for(int j = 0; j < height; j++) {
            tileMap[i][j] = new int[width]; // ancho del tilemap
        }
    }

    int l = 0; // capa actual en la que nos encontramos
    while(layer) {
        data = layer->FirstChildElement("data")->FirstChildElement("tile");

        while(data) {
            for(int i = 0; i < height; i++) {
                for(int j = 0; j < width; j++) {
                    data->QueryIntAttribute("gid", &tileMap[l][i][j]);
                    // COMPROBAR ESTA LINEA, SU UTILIDAD
                    // if(n == numLayers -)
                    data = data->NextSiblingElement("tile");
                }
            }
        }
        layer = layer->NextSiblingElement("layer");
        l++;

    }

}


void Map::getLayers()
{
    while(layer){
        numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
}


void Map::creaColisiones()
{
    // TENGO QUE CREAR COLISIONES EN BASE A DONDE ESTÁN COLOCADOS LOS RECTÁNGULOS.
    layer = xmlMap->FirstChildElement("objectgroup");
    data = layer->FirstChildElement("object");

    while(layer) {
//        std::cout << "nombre capa: " << (string)layer->Attribute("name") << std::endl;
        data = layer->FirstChildElement("object");

        while(data) {
            int x, y, w, h;
            data->QueryIntAttribute("x", &x);
            data->QueryIntAttribute("y", &y);
            data->QueryIntAttribute("width", &w);
            data->QueryIntAttribute("height", &h);

            sf::Vector2f pos(x, y);
            sf::Vector2f tam(w, h);

            string nombre = (string)layer->Attribute("name");

            if(nombre.compare("pl_nodestruibles") == 0) // Plataformas normales
            {
                Collider col(tam, pos, 0);
                colisiones.push_back(col);

            }
            else if(nombre.compare("escaleras") == 0) // Escaleras
            {
                Collider col (tam, pos, 1);
                colisiones.push_back(col);

            }
            else if(nombre.compare("esferas") == 0) // esferas
            {
                Objects* esfera = new Objects(pos);
                esferas.push_back(esfera);
            }
            else if(nombre.compare("pl_destruibles") == 0)
            {
                Blocks* block = new Blocks (tam, pos);
                destrBlocks.push_back(block);
            }

            data = data->NextSiblingElement("object");
        }

        layer = layer->NextSiblingElement("objectgroup");

    }


}



void Map::createSprites()
{
    mapSprite = new Sprite***[numLayers];

    for(int i = 0; i < numLayers; i++) {
        mapSprite[i] = new Sprite**[height];
        for(int j = 0; j < height; j++) {
            mapSprite[i][j] = new Sprite*[width];
            for(int z = 0; z < width; z++) {
                mapSprite[i][j][z] = new Sprite;
            }
        }
    }

    int cols = tileSetTexture.getSize().x / tileWidth;
    int rows = tileSetTexture.getSize().y / tileHeight;

    tilesetSprite = new Sprite[rows*cols];

    int n = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            tilesetSprite[n].setTexture(tileSetTexture);
            tilesetSprite[n].setTextureRect(IntRect(j*tileWidth, i*tileHeight, tileWidth, tileHeight));
            n++;
        }
    }

    for(int i = 0; i < numLayers; i++) {
        for(int j = 0; j < height; j++) {
            for(int k = 0; k < width; k++) {

                gid = tileMap[i][j][k]-1;

                if(gid > 0 && gid < width*height) {
                    mapSprite[i][j][k] = new Sprite(tileSetTexture, tilesetSprite[gid].getTextureRect());
                    mapSprite[i][j][k]->setPosition(k*tileWidth, j*tileHeight);

                } else {
                    mapSprite[i][j][k] = NULL;
                }

            }
        }
    }

}

void Map::update(Player* &p, Enemy* &e)
{
    for(int i = 0; i < colisiones.size(); i++) {
        colisiones.at(i).update(*p, *e);
    }

    for(int i = 0; i < esferas.size(); i++) {

        if(esferas.at(i)->update(*p)){
            p->setSpheres();
            delete esferas.at(i);
            esferas.erase(esferas.begin()+i);
        }
    }

    for(int i = 0; i < destrBlocks.size(); i++) {
        destrBlocks.at(i)->update(*p);

        if(destrBlocks.at(i)->isDestroyed()) {
            delete destrBlocks.at(i);
            destrBlocks.erase(destrBlocks.begin()+i);
        }

    }

}


void Map::draw(RenderWindow& target)
{

    for(int l = 0; l < numLayers; l++) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                if(mapSprite[l][y][x] !=NULL) {
                    target.draw(*(mapSprite[l][y][x]));
                }
            }
        }
    }

//    for(int i = 0; i < colisiones.size(); i++) {
//        colisiones.at(i).draw(target);
//    }

    for(int i = 0; i < esferas.size(); i++) {
        esferas.at(i)->draw(target);
    }

    for(int i = 0; i < destrBlocks.size(); i++) {
        destrBlocks.at(i)->draw(target);
    }


}

