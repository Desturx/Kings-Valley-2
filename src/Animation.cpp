#include "Animation.h"

/*
    DISCLAIMER:
    ****
    ESTA PARTE LA HICE YO EN EL PROYECTO GRUPAL, PERO HE CONSIDERADO MEJORARLA PARA
    ESTE PROYECTO
    ****
*/

Animation::Animation()
{

}


Animation::~Animation()
{
    //dtor
}

void Animation::setAnimation(char* nTextura, sf::IntRect firstF, sf::IntRect finalF, int incremento, float tiempo)
{
    if(!texture.loadFromFile(nTextura)){
        std::cout << "ERROR AL CARGAR TEXTURA";
    }
    this->firstF = firstF;
    this->finalF = finalF;
    this->incremento = incremento;

    actualFrame = firstF;
    switchTime = tiempo;
    sprite = sf::Sprite(texture, actualFrame);
    sprite.setOrigin(firstF.width/2, firstF.height/2);

    isPlaying = true;
    loop = true;
    finished = false;
    dirSprite = 1;

}

void Animation::update(sf::Vector2f movement, float mTime)
{
    // Updatear la animación para que cambie de sprite
    float delta = clock.getElapsedTime().asSeconds();

    if(delta >= switchTime && isPlaying && !finished){
        clock.restart();
        if(!loop) {
            if(actualFrame.left != finalF.left) {
                actualFrame.left += incremento;
            } else {
                finished = true;
            }

            sprite.setTextureRect(actualFrame);
        } else if(loop) {
           if(actualFrame.left == finalF.left) {
            actualFrame.left = firstF.left;

            } else {
                actualFrame.left += incremento;
            }

            sprite.setTextureRect(actualFrame);
        }


    }
    // Muevo el sprite con el tiempo y el vector que recibo por parametro
    sprite.move(movement*mTime);
}


void Animation::noLoop()
{
    // Si usamos este metodo es que queremos reproducir la animacion x veces antes de que pare
    loop = false;
}


void Animation::doLoop()
{
    loop = true;
}

bool Animation::animFinished()
{
    return finished;
}


void Animation::stop()
{
    isPlaying = false;
}

void Animation::play()
{
    isPlaying = true;
}

void Animation::flip(char dir)
{
    if(dir == 'l') {
        dirSprite = -1;
    } else if(dir == 'r'){
        dirSprite = 1;
    }
    sprite.setScale(dirSprite, 1);

}

void Animation::setPosition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void Animation::setOrigin(float x, float y)
{
    sprite.setOrigin(x, y);
}

int Animation::getDir()
{
    return dirSprite;
}

void Animation::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

