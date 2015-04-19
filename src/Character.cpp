#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Animation.h"
#include <iostream>

int randint(int low, int high);
int randint(int low, int high, int seed);
int distance(float speed, float time);

using namespace sf;

int FLOOR = 663;

Character::Character(std::string name, Texture* _weaponTexture, Texture* dyingTexture, Vector2f _position)
{
    state = STATE_STANDING;
    graphicState = STATE_STANDING;

    int seed = 0;
    for (int i = 0; i < name.length(); i++)
    {
        seed += (int)(name[i]);
    }

    health = randint(75, 125, seed);
    maxHealth = health;
    weight = randint(48, 400, seed);
    strength = randint(5, 20, seed);
    jump = randint(12, 28, seed);
    speed = randint(75, 120, seed);
    position = _position;
    velocity = Vector2f(0, 0);
    weapon = (Weapon)(randint(0, 6, seed));
    flip = false;
    weaponTexture = _weaponTexture;
    wasEnterPressed = false;
    isHit = false;
    deadTexture = dyingTexture;
}

void Character::drawWeapon(RenderWindow* window, Vector2f weaponPos, Vector2f weaponFlipPos, float weaponRotation)
{
    //weaponPos is the position of the weapon-holding hand relative to the origin of the Character
    Sprite weaponSprite;
    weaponSprite.setTexture(*weaponTexture);
    weaponSprite.setTextureRect(IntRect(weapon * 300, 0, 300, 150));
    weaponSprite.setOrigin(150, 75);
    weaponSprite.setPosition(position + weaponPos);
    weaponSprite.setRotation(weaponRotation);

    weaponSprite.setColor(Color(255, 255, 255, 255));

    if (flip)
    {
        weaponSprite.scale(-1, 1);
        weaponSprite.setPosition(position - weaponFlipPos);
        weaponSprite.setRotation(360 - weaponRotation);
    }

    window->draw(weaponSprite);
}

//This is where the magic happens
//jk there are loads of magic numbers here
void Character::draw(RenderWindow* window, Time dt, Animation* anRun, Animation* anIdle, Animation* anCrouch, Animation* anJump,
                                                    Animation* anFall, Animation* annAtk, Animation* andAtk, Animation* anuAtk,
                                                    Animation* anHit, Animation* anDie)
{
    switch(graphicState)
    {
    case(STATE_STANDING):
        anIdle->setPosition(position);
        anIdle->play(window, dt, flip);
        if (anIdle->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(223, 33), Vector2f(223, -33), 15);
        else if (anIdle->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(226, 36), Vector2f(226, -36), 15);
        break;
    case(STATE_WALKING_LEFT):
        anRun->setPosition(position);
        anRun->play(window, dt, flip);
        if (anRun->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(0, 0), Vector2f(-12, -12), 100);
        else if (anRun->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(0, 0), Vector2f(11, -15), 100);
        else if (anRun->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(0, 0), Vector2f(-1, 14), 100);
        else if (anRun->getCurrentFrame() == 3)
            drawWeapon(window, Vector2f(0, 0), Vector2f(14, 11), 100);
        else if (anRun->getCurrentFrame() == 4)
            drawWeapon(window, Vector2f(0, 0), Vector2f(-2, 2), 100);
        else if (anRun->getCurrentFrame() == 5)
            drawWeapon(window, Vector2f(0, 0), Vector2f(-14, 12), 100);
        break;
    case(STATE_WALKING_RIGHT):
        anRun->setPosition(position);
        anRun->play(window, dt, flip);
        if (anRun->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(-12, -12), Vector2f(0, 0), 100);
        else if (anRun->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(11, -33), Vector2f(0, 0), 100);
        else if (anRun->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(-1, 14),Vector2f(0, 0), 100);
        else if (anRun->getCurrentFrame() == 3)
            drawWeapon(window, Vector2f(14, 11), Vector2f(0, 0), 100);
        else if (anRun->getCurrentFrame() == 4)
            drawWeapon(window, Vector2f(-2, 2), Vector2f(0, 0), 100);
        else if (anRun->getCurrentFrame() == 5)
            drawWeapon(window, Vector2f(-14, 18), Vector2f(0, 0), 100);
        break;
    case(STATE_CROUCHING):
        anCrouch->setPosition(position);
        anCrouch->play(window, dt, flip);
        drawWeapon(window, Vector2f(0, 29), Vector2f(0, -29), 100);
        break;
    case(STATE_JUMPING):
        anJump->setPosition(position);
        anJump->play(window, dt, flip);
        drawWeapon(window, Vector2f(-75, 29), Vector2f(-75, -29), 95);
        break;
    case(STATE_FALLING):
        anFall->setPosition(position);
        anFall->play(window, dt, flip);
        drawWeapon(window, Vector2f(-75, 29), Vector2f(-75, -29), 95);
        break;
    case(STATE_NEUTRALATTACK):
        annAtk->setPosition(position);
        annAtk->play(window, dt, flip);
        if (annAtk->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(250, 10), Vector2f(250, -10), 0);
        else if (annAtk->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(294, -25), Vector2f(294, 25), 0);
        else if (annAtk->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(345, -25), Vector2f(345, 25), 0);
        break;
    case(STATE_UPATTACK):
        anuAtk->setPosition(position);
        anuAtk->play(window, dt, flip);
        if (anuAtk->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(-284, 143), Vector2f(-284, -143), 128);
        else if (anuAtk->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(-317, -187), Vector2f(-317, 187), 203);
        else if (anuAtk->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(254, -193), Vector2f(254, 193), 328);
        else if (anuAtk->getCurrentFrame() == 3)
            drawWeapon(window, Vector2f(313, 104), Vector2f(313, -104), 29);
        break;
    case(STATE_DOWNATTACK):
        andAtk->setPosition(position);
        andAtk->play(window, dt, flip);
        if (andAtk->getCurrentFrame() == 0 || andAtk->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(300, 78), Vector2f(300, -78), 0.0f);
        else if (andAtk->getCurrentFrame() == 1 || andAtk->getCurrentFrame() == 3)
            drawWeapon(window, Vector2f(-240, 76), Vector2f(-240, -76), 0.0f);
        break;
    case(STATE_HIT):
        anHit->setPosition(position);
        anHit->play(window, dt, flip);
        if (anHit->getCurrentFrame() == 0 || anHit->getCurrentFrame() == 2 || anHit->getCurrentFrame() == 4)
            drawWeapon(window, Vector2f(40, 165), Vector2f(0, 0), 40.0f);
        break;
    case(STATE_DYING):
        anDie->setPosition(position);
        anDie->play(window, dt, flip);
        if (anDie->getCurrentFrame() == 0)
            drawWeapon(window, Vector2f(102, -59), Vector2f(0, 0), 340.0f);
        else if (anDie->getCurrentFrame() == 1)
            drawWeapon(window, Vector2f(216, 164), Vector2f(0, 0), 0.0f);
        else if (anDie->getCurrentFrame() == 2)
            drawWeapon(window, Vector2f(380, 180), Vector2f(0, 0), 0.0f);
        break;
    /*case(STATE_DEAD):
        Sprite dead;
        dead.setTexture(*deadTexture);
        dead.setPosition(position);
        dead.setOrigin(237, 195);
        dead.setTextureRect(IntRect(950, 0, 475, 390));
        window->draw(dead);
        drawWeapon(window, Vector2f(380, 180), Vector2f(0, 0), 0.0f);*/
    }
}

void Character::update(Time dt, Animation* annAtk, Animation* andAtk, Animation* anuAtk, Animation* anHit, Animation* anDie)
{
    totalTime += dt;

    switch(state)
    {
    case(STATE_STANDING):
        graphicState = STATE_STANDING;

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            state = STATE_WALKING_LEFT;
            graphicState = STATE_WALKING_LEFT;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            state = STATE_WALKING_RIGHT;
            graphicState = STATE_WALKING_RIGHT;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            state = STATE_CROUCHING;
            graphicState = STATE_CROUCHING;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            state = STATE_JUMPING;
            graphicState = STATE_JUMPING;
        }

        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            state = STATE_NEUTRALATTACK;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed && Keyboard::isKeyPressed(Keyboard::W))
            state = STATE_UPATTACK;

        hitbox = IntRect(-100, -100, 0, 0);

        velocity.x = 0;
        break;
    case(STATE_WALKING_LEFT):
        if (!Keyboard::isKeyPressed(Keyboard::A))
            state = STATE_STANDING;
        velocity.x = -10;
        flip = true;
        if (Keyboard::isKeyPressed(Keyboard::Space))
            state = STATE_JUMPING;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            state = STATE_NEUTRALATTACK;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed && Keyboard::isKeyPressed(Keyboard::W))
            state = STATE_UPATTACK;
        break;
    case(STATE_WALKING_RIGHT):
        if (!Keyboard::isKeyPressed(Keyboard::D))
            state = STATE_STANDING;
        velocity.x = 10;
        flip = false;
        if (Keyboard::isKeyPressed(Keyboard::Space))
            state = STATE_JUMPING;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            state = STATE_NEUTRALATTACK;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed && Keyboard::isKeyPressed(Keyboard::W))
            state = STATE_UPATTACK;
        break;
    case(STATE_CROUCHING):
        if (!Keyboard::isKeyPressed(Keyboard::S))
            state = STATE_STANDING;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            state = STATE_DOWNATTACK;
        break;
    case(STATE_JUMPING):
        if (position.y == FLOOR)
        {
            velocity.y = -(jump);
        }
        if (position.y > FLOOR)
            state = STATE_STANDING;

        //flip = false;
        if (Keyboard::isKeyPressed(Keyboard::D))
            velocity.x = 10;
        else if (!Keyboard::isKeyPressed(Keyboard::D) && velocity.x > 0)
            velocity.x--;

        if (Keyboard::isKeyPressed(Keyboard::A))
            velocity.x = -10;
        else if (!Keyboard::isKeyPressed(Keyboard::A) && velocity.x < 0)
            velocity.x++;

        if (velocity.y >= 0)
            graphicState = STATE_FALLING;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            state = STATE_NEUTRALATTACK;
        if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed && Keyboard::isKeyPressed(Keyboard::W))
        {
            state = STATE_UPATTACK;
        }
        break;
    case(STATE_NEUTRALATTACK):
        velocity.x = 0;
        graphicState = STATE_NEUTRALATTACK;
        if (annAtk->isAnimationOver()) //animation ends
            state = STATE_STANDING;
        if (annAtk->getCurrentFrame() == 0 && flip == false)
            hitbox = IntRect(position.x + 90, position.y - 65, 300, 150);
        else if (annAtk->getCurrentFrame() == 1 && flip == false)
            hitbox = IntRect(position.x + 125, position.y - 105, 300, 150);
        else if (annAtk->getCurrentFrame() == 2 && flip == false)
            hitbox = IntRect(position.x + 171, position.y - 105, 300, 150);
        else if (annAtk->getCurrentFrame() == 0 && flip == true)
            hitbox = IntRect(position.x - 390, position.y - 65, 300, 150);
        else if (annAtk->getCurrentFrame() == 1 && flip == true)
            hitbox = IntRect(position.x - 425, position.y - 105, 300, 150);
        else if (annAtk->getCurrentFrame() == 2 && flip == true)
            hitbox = IntRect(position.x - 471, position.y - 105, 300, 150);
        break;
    case(STATE_UPATTACK):
        velocity.x = 0;
        graphicState = STATE_UPATTACK;
        if (anuAtk->isAnimationOver())
            state = STATE_STANDING;
        if ((anuAtk->getCurrentFrame() == 0 || anuAtk->getCurrentFrame() == 1) && flip == false)
            hitbox = IntRect(position.x - 400, position.y - 271, 400, 480);
        else if ((anuAtk->getCurrentFrame() == 2 || anuAtk->getCurrentFrame() == 3) && flip == false)
            hitbox = IntRect(position.x, position.y - 271, 400, 480);
        else if ((anuAtk->getCurrentFrame() == 0 || anuAtk->getCurrentFrame() == 1) && flip == true)
            hitbox = IntRect(position.x, position.y - 271, 400, 480);
        else if ((anuAtk->getCurrentFrame() == 2 || anuAtk->getCurrentFrame() == 3) && flip == true)
            hitbox = IntRect(position.x - 400, position.y - 271, 400, 480);
        break;
    case(STATE_DOWNATTACK):
        graphicState = STATE_DOWNATTACK;
        if (andAtk->isAnimationOver())
            state = STATE_STANDING;
        if ((andAtk->getCurrentFrame() == 0 || andAtk->getCurrentFrame() == 2) && flip == false)
            hitbox = IntRect(position.x + 133, position.y - 0, 300, 150);
        else if ((andAtk->getCurrentFrame() == 1 || andAtk->getCurrentFrame() == 3) && flip == false)
            hitbox = IntRect(position.x - 433, position.y - 0, 300, 150);
        else if ((andAtk->getCurrentFrame() == 0 || andAtk->getCurrentFrame() == 2) && flip == true)
            hitbox = IntRect(position.x - 433, position.y - 0, 300, 150);
        else if ((andAtk->getCurrentFrame() == 1 || andAtk->getCurrentFrame() == 3) && flip == true)
            hitbox = IntRect(position.x + 133, position.y - 0, 300, 150);
        break;
    case(STATE_HIT):
        velocity.x = 0;
        graphicState = STATE_HIT;
        if (anHit->isAnimationOver())
        {
            if (health <= 0)
                state = STATE_DYING;
            else if (health > 0)
                state = STATE_STANDING;
        }

        break;
    case(STATE_DYING):
        graphicState = STATE_DYING;
        break;
    }

    if (isHit && (totalTime.asMilliseconds() - lastHit.asMilliseconds() > 750))
    {
        state = STATE_HIT;
        lastHit = totalTime;
    }
    else if (totalTime.asMilliseconds() - lastHit.asMilliseconds() < 750)
    {
        isHit = false;
    }

    if (position.y < FLOOR)
        velocity.y += 1; //gravity
    else if (position.y > FLOOR)
    {
        position.y = FLOOR;
        velocity.y = 0;
    }

    position.x += velocity.x * speed * dt.asSeconds();
    position.y += velocity.y * speed * dt.asSeconds();

    wasEnterPressed = Keyboard::isKeyPressed(Keyboard::Return);

    //std::cout << state << "\n";
}

void Character::AIupdate(Time dt, Animation* annAtkEn, Animation* andAtkEn, Animation* anuAtkEn, Animation* anHitEn, Animation* anDieEn)
{
    totalTime += dt;

    switch(state)
    {
    case(STATE_STANDING):
        graphicState = STATE_STANDING;
        break;
    case(STATE_WALKING_LEFT):
        break;
    case(STATE_WALKING_RIGHT):
        break;
    case(STATE_CROUCHING):
        break;
    case(STATE_JUMPING):
        break;
    case(STATE_FALLING):
        break;
    case(STATE_NEUTRALATTACK):
        velocity.x = 0;
        graphicState = STATE_NEUTRALATTACK;
        if (annAtkEn->isAnimationOver()) //animation ends
            state = STATE_STANDING;
        if (annAtkEn->getCurrentFrame() == 0 && flip == false)
            hitbox = IntRect(position.x + 90, position.y - 65, 300, 150);
        else if (annAtkEn->getCurrentFrame() == 1 && flip == false)
            hitbox = IntRect(position.x + 125, position.y - 105, 300, 150);
        else if (annAtkEn->getCurrentFrame() == 2 && flip == false)
            hitbox = IntRect(position.x + 171, position.y - 105, 300, 150);
        else if (annAtkEn->getCurrentFrame() == 0 && flip == true)
            hitbox = IntRect(position.x - 390, position.y - 65, 300, 150);
        else if (annAtkEn->getCurrentFrame() == 1 && flip == true)
            hitbox = IntRect(position.x - 425, position.y - 105, 300, 150);
        else if (annAtkEn->getCurrentFrame() == 2 && flip == true)
            hitbox = IntRect(position.x - 471, position.y - 105, 300, 150);
        break;
    case(STATE_UPATTACK):
        break;
    case(STATE_DOWNATTACK):
        break;
    case(STATE_HIT):
        velocity.x = 0;
        graphicState = STATE_HIT;
        if (anHitEn->isAnimationOver())
        {
            if (health <= 0)
                state = STATE_DYING;
            else if (health > 0)
                state = STATE_STANDING;
        }
        break;
    case(STATE_DYING):
        graphicState = STATE_DYING;
        break;
    }



    if (position.y < FLOOR)
        velocity.y += 1; //gravity
    else if (position.y > FLOOR)
    {
        position.y = FLOOR;
        velocity.y = 0;
    }

    position.x += velocity.x * speed * dt.asSeconds();
    position.y += velocity.y * speed * dt.asSeconds();

    //AI
}

bool Character::checkHit(IntRect hitbox, int enemyStrength) //<- this is the enemys hitbox
{
    isHit = hitbox.contains(position.x, position.y);
    if (isHit && (totalTime.asMilliseconds() - lastHit.asMilliseconds() > 750) && state != STATE_DYING)
    {
        state = STATE_HIT;
        lastHit = totalTime;
        health -= enemyStrength;
    }
    else if (totalTime.asMilliseconds() - lastHit.asMilliseconds() < 750)
    {
        isHit = false;
    }
}
