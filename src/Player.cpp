#include "Player.h"
#include <iostream>

Player::Player(sf::Vector2f pos)
{
    pCenter = pos;

    movement = sf::Vector2f(0.f, 0.f);
    speed = .20f;

    // Jump
    grav = 0.006f;



    hitbox = sf::RectangleShape(sf::Vector2f(64,64));
    hitbox.setFillColor(sf::Color::Blue);
    hitbox.setOrigin(64/2, 64/2);
    hitbox.setPosition(pos);

    up = false;
    down = true;
    right = false;
    left = false;
    stairs = false;
    isOnAir = false;
    destrBloque = false;
    currentTool = -1;
    canDestroy = false;
    gameOver = false;
    restartLevel = false;
    godMode = false;


    // Animaciones sin arma
    run.setAnimation("resources/sprites/sin_arma.png", sf::IntRect(0, 0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);
    climb.setAnimation("resources/sprites/sin_arma.png", sf::IntRect(64*4, 0, 64, 64), sf::IntRect(64*5, 0, 64, 64), 64, 0.15f);
    jump.setAnimation("resources/sprites/sin_arma.png", sf::IntRect(64*6, 0, 64, 64), sf::IntRect(64*6, 0, 64, 64), 64, 0.15f);

    // Animaciones con pico
    p_run.setAnimation("resources/sprites/con_pico.png", sf::IntRect(0, 0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);
    p_climb.setAnimation("resources/sprites/con_pico.png", sf::IntRect(64*4, 0, 64, 64), sf::IntRect(64*5, 0, 64, 64), 64, 0.15f);


    // Animaciones con taladro-drill
    d_run.setAnimation("resources/sprites/con_taladro.png", sf::IntRect(0, 0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);
    d_run.setAnimation("resources/sprites/con_taladro.png", sf::IntRect(0, 0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);


    //Animaciones de muerte
    dying.setAnimation("resources/sprites/dead.png", sf::IntRect(0, 0, 64, 64), sf::IntRect(64*3, 0, 64, 64), 64, 0.15f);
    dead.setAnimation("resources/sprites/dead.png", sf::IntRect(64*4, 0, 64, 64), sf::IntRect(64*4, 0, 64, 64), 64, 0.15f);

    changeAnimation(&run);



    c_izq = sf::RectangleShape(sf::Vector2f(3, 48));
    c_izq.setPosition(pos.x - 30, pos.y - 48/2);
    c_izq.setFillColor(sf::Color::Green);

    c_der = sf::RectangleShape(sf::Vector2f(3, 48));
    c_der.setPosition(pos.x + 30, pos.y - 48/2);
    c_der.setFillColor(sf::Color::Green);

    c_abj = sf::RectangleShape(sf::Vector2f(45, 3));
    c_abj.setPosition(pos.x - 45/2, pos.y + 35);
    c_abj.setFillColor(sf::Color::Green);

    c_arr = sf::RectangleShape(sf::Vector2f(43, 3));
    c_arr.setPosition(pos.x - 45/2, pos.y - 30);
    c_arr.setFillColor(sf::Color::Green);

}

Player::~Player()
{
    delete actual;
}

void Player::changeAnimation(Animation* newAnimation) {
    actual = newAnimation;
    actual->setPosition(hitbox.getPosition());
}

void Player::update(float delta)
{

    if(!stopped) {

        moving(delta);

        // Acciones con el espacio
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(!isJumping && currentTool == -1)
            {
                isJumping = true;
                isOnAir = true;
                jumping(delta);
            }
            else if(currentTool >= 0 && canDestroy)
            {
                changeAnimation(&run);
                cdArma.restart();
                destrBloque = true;
                stop();
            }


        }

        // Muerte del juegador pulsando la x
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            kill();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::G) && cdGod.getElapsedTime().asSeconds() >= .5f) {
            if(godMode) {
                godMode = false;
                std::cout << "GODMODE DESACTIVADO" << std::endl;
            } else {
                godMode = true;
                std::cout << "GODMODE ACTIVADO" << std::endl;

            }
            cdGod.restart();
        }


        if(!down && !stairs && !isOnAir)
            movement.y += grav*delta;

        controlPosition();

        actual->update(movement, delta);

        if(isJumping && up) {
            hitbox.move(0,0);
        }

        moveColliders(delta);
        hitbox.move(movement*delta);


        if(down) {
            isJumping = false;
        }
        up = false;
        down = false;
        right = false;
        left = false;
        stairs = false;
        isOnAir = false;



    }else {
        if(cdArma.getElapsedTime().asSeconds() >= 1.f && !gameOver) {
            destrBloque = false;
            resume();
            currentTool = -1;
        }

        if(gameOver) {
            if(actual != &dying && deadTime.getElapsedTime().asSeconds() <= 2.f){
                changeAnimation(&dying);
            }
            if(deadTime.getElapsedTime().asSeconds() <= 2.f) {
                actual->update(sf::Vector2f(0,0), 0);
            } else if(deadTime.getElapsedTime().asSeconds() > 2.f) {
                if(actual != &dead) {
                    changeAnimation(&dead);
                    groundTime.restart();
                }
                if(groundTime.getElapsedTime().asSeconds() >= .8f) {
                    restartLevel = true;
                }

            }
        }
    }


}

void Player::kill() {
    if(!godMode) {
          gameOver = true;
        stop();
        deadTime.restart();
    }

}

void Player::controlPosition()
{
    if((hitbox.getPosition().y >= 760.f || hitbox.getPosition().y <= 0.f) && stairs) {
//        std::cout << "HA PASADO EL LÍMITE" << std::endl;
        if(hitbox.getPosition().y >= 760.f) { // la distancia hacia abajo
            hitbox.setPosition(hitbox.getPosition().x, 0);
            c_izq.setPosition(hitbox.getPosition().x - 30, hitbox.getPosition().y - 48/2);
            c_der.setPosition(hitbox.getPosition().x + 30, hitbox.getPosition().y - 48/2);
            c_abj.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y + 30);
            c_arr.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y - 30);
//            std::cout << "entra en la primera" << std::endl;

            actual->setPosition(hitbox.getPosition());
        } else if(hitbox.getPosition().y <= 0) {
            hitbox.setPosition(hitbox.getPosition().x, 760);
            c_izq.setPosition(hitbox.getPosition().x - 30, hitbox.getPosition().y - 48/2);
            c_der.setPosition(hitbox.getPosition().x + 30, hitbox.getPosition().y - 48/2);
            c_abj.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y + 30);
            c_arr.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y - 30);

            actual->setPosition(hitbox.getPosition());
        }
    } else if(hitbox.getPosition().y >= 760.f || hitbox.getPosition().y <= 0.f){
        hitbox.setPosition(571, 580);
        c_izq.setPosition(hitbox.getPosition().x - 30, hitbox.getPosition().y - 48/2);
        c_der.setPosition(hitbox.getPosition().x + 30, hitbox.getPosition().y - 48/2);
        c_abj.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y + 30);
        c_arr.setPosition(hitbox.getPosition().x - 50/2, hitbox.getPosition().y - 30);
        actual->setPosition(hitbox.getPosition());

    }
}

void Player::jumping(float delta)
{
    movement.y = (movement.y - (speed*4.f)) - grav*delta;
    movement.x = movement.x * 1.8f;

    changeAnimation(&jump);
}

void Player::moving(float delta)
{
    using namespace sf;

    movement = sf::Vector2f(0.f, 0.f);

    if(Keyboard::isKeyPressed(Keyboard::Left) && !left) {
        if(currentTool == -1) // si no lleva arma
        {
            if(actual != &run && !isJumping){
                changeAnimation(&run);
            }
        }
        else if(currentTool == 0) //  si es el pico
        {
            if(actual != &p_run)
                changeAnimation(&p_run);
        }
        else if(currentTool == 1)
        {
            if(actual != &d_run)
                changeAnimation(&d_run);
        }

        movement.x -= speed;
        actual->flip('l');
    }

    if(Keyboard::isKeyPressed(Keyboard::Right) && !right) {
        if(currentTool == -1)
        {
            if(actual != &run && !isJumping){
                changeAnimation(&run);
            }
        }
        else if(currentTool == 0)
        {
            if(actual != &p_run){
                changeAnimation(&p_run);
            }
        }
        else if(currentTool == 1)
        {
            if(actual!= &d_run)
                changeAnimation(&d_run);
        }

        movement.x += speed;
        actual->flip('r');
    }

    if(Keyboard::isKeyPressed(Keyboard::Up) && !up && stairs) {
        if(currentTool == -1)
        {
            if(actual != &climb && !isJumping){
                changeAnimation(&climb);
            }
        }
        else if(currentTool == 0)
        {
            if(actual != &p_climb){
                changeAnimation(&p_climb);
            }
        }
        else if(currentTool == 1)
        {
            if(actual != &d_climb)
                changeAnimation(&d_climb);
        }
        movement.y -= .15f;

    }

    if(Keyboard::isKeyPressed(Keyboard::Down) && !down && stairs) {
        if(currentTool == -1)
        {
            if(actual != &climb && !isJumping){
                changeAnimation(&climb);
            }
        }
        else if(currentTool == 0)
        {
            if(actual != &p_climb){
                changeAnimation(&p_climb);
            }
        }
        else if(currentTool == 1)
        {
            if(actual != &d_climb)
                changeAnimation(&d_climb);
        }
        movement.y += .15f;
    }

    if(movement.x == 0 && movement.y == 0) {
        actual->stop();
    } else {
        actual->play();
    }
}


void Player::moveColliders(float delta)
{
    c_abj.move(delta*movement);
    c_arr.move(delta*movement);
    c_izq.move(delta*movement);
    c_der.move(delta*movement);
}

void Player::setCol(std::string col, bool val)
{
    if(col.compare("down") == 0) {
        down = val;
    } else if(col.compare("up") == 0) {
        up = val;
    } else if(col.compare("right") == 0) {
        right = val;
    } else if(col.compare("left") == 0) {
        left = val;
    } else if(col.compare("stairs") == 0) {
        stairs = val;
    }
}

void Player::stop()
{
    stopped = true;
}

void Player::resume()
{
    stopped = false;
}

void Player::setTool(int t)
{
    currentTool = t;
    if(t == 0) {
        changeAnimation(&p_run);
    }
}

sf::FloatRect Player::getGlobalBounds()
{
    return hitbox.getGlobalBounds();
}

sf::FloatRect Player::boundsDown()
{
    return c_abj.getGlobalBounds();
}

sf::FloatRect Player::boundsUp()
{
    return c_arr.getGlobalBounds();
}

sf::FloatRect Player::boundsRight()
{
    return c_der.getGlobalBounds();
}

sf::FloatRect Player::boundsLeft()
{
    return c_izq.getGlobalBounds();
}

bool Player::getIsOnAir()
{
    return isJumping;
}

bool Player::getDestrBloque()
{
    return destrBloque;
}

int Player::getTool()
{
    return currentTool;
}

bool Player::getGameOver()
{
    return restartLevel;
}

void Player::setCanDestroy(bool val)
{
    canDestroy = val;
}

void Player::setSpheres()
{
    sph_collected++;
}

int Player::getSpheres()
{
    return sph_collected;
}

void Player::drawColliders(sf::RenderWindow& window)
{
    window.draw(c_izq);
    window.draw(c_der);
    window.draw(c_abj);
    window.draw(c_arr);
}

void Player::doDraw()
{
    drawing = true;
}

void Player::dontDraw()
{
    drawing = false;
}



void Player::draw(sf::RenderWindow& window)
{
    if(drawing) {
        actual->draw(window);
    }


}
