//Presenting... "Pen Pals"!

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "Animation.h"
#include "Character.h"

int randint(int low, int high);
int randint(int low, int high, int seed);
void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture);
void drawFloat(RenderWindow* window, float num, Vector2f position, Texture* fontTexture);

using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Pen Pals");
    window.setVerticalSyncEnabled(true);

    Texture runTexture;
    if (!runTexture.loadFromFile("Player/run.png"))
        return EXIT_FAILURE;
    Texture idleTexture;
    if (!idleTexture.loadFromFile("Player/idle.png"))
        return EXIT_FAILURE;
    Texture crouchTexture;
    if (!crouchTexture.loadFromFile("Player/crouch.png"))
        return EXIT_FAILURE;
    Texture jumpTexture;
    if (!jumpTexture.loadFromFile("Player/jump.png"))
        return EXIT_FAILURE;
    Texture fallTexture;
    if (!fallTexture.loadFromFile("Player/fall.png"))
        return EXIT_FAILURE;
    Texture nAtkTexture;
    if (!nAtkTexture.loadFromFile("Player/nattack.png"))
        return EXIT_FAILURE;
    Texture dAtkTexture;
    if (!dAtkTexture.loadFromFile("Player/dattack.png"))
        return EXIT_FAILURE;
    Texture uAtkTexture;
    if (!uAtkTexture.loadFromFile("Player/uattack.png"))
        return EXIT_FAILURE;
    Texture hitTexture;
    if (!hitTexture.loadFromFile("Player/hit.png"))
        return EXIT_FAILURE;
    Texture dyingTexture;
    if (!dyingTexture.loadFromFile("Player/dying.png"))
        return EXIT_FAILURE;


    Texture runEnemyTexture;
    if (!runEnemyTexture.loadFromFile("Enemy/run.png"))
        return EXIT_FAILURE;
    Texture idleEnemyTexture;
    if (!idleEnemyTexture.loadFromFile("Enemy/idle.png"))
        return EXIT_FAILURE;
    Texture crouchEnemyTexture;
    if (!crouchEnemyTexture.loadFromFile("Enemy/crouch.png"))
        return EXIT_FAILURE;
    Texture jumpEnemyTexture;
    if (!jumpEnemyTexture.loadFromFile("Enemy/jump.png"))
        return EXIT_FAILURE;
    Texture fallEnemyTexture;
    if (!fallEnemyTexture.loadFromFile("Enemy/fall.png"))
        return EXIT_FAILURE;
    Texture nAtkEnemyTexture;
    if (!nAtkEnemyTexture.loadFromFile("Enemy/nattack.png"))
        return EXIT_FAILURE;
    Texture dAtkEnemyTexture;
    if (!dAtkEnemyTexture.loadFromFile("Enemy/dattack.png"))
        return EXIT_FAILURE;
    Texture uAtkEnemyTexture;
    if (!uAtkEnemyTexture.loadFromFile("Enemy/uattack.png"))
        return EXIT_FAILURE;
    Texture hitEnemyTexture;
    if (!hitEnemyTexture.loadFromFile("Enemy/hit.png"))
        return EXIT_FAILURE;
    Texture dyingEnemyTexture;
    if (!dyingEnemyTexture.loadFromFile("Enemy/dying.png"))
        return EXIT_FAILURE;


    Texture weaponTexture;
    if (!weaponTexture.loadFromFile("weapons.png"))
        return EXIT_FAILURE;
    Texture bgTexture;
    if (!bgTexture.loadFromFile("bg1080.png"))
        return EXIT_FAILURE;
    Texture font;
    if (!font.loadFromFile("font.png"))
        return EXIT_FAILURE;
    Texture healthBarPlayerEmpty;
    if (!healthBarPlayerEmpty.loadFromFile("Player/healthEmpty.png"))
        return EXIT_FAILURE;
    Texture healthBarPlayerFull;
    if (!healthBarPlayerFull.loadFromFile("Player/healthFull.png"))
        return EXIT_FAILURE;
    Texture healthBarEnemyEmpty;
    if (!healthBarEnemyEmpty.loadFromFile("Enemy/healthEmpty.png"))
        return EXIT_FAILURE;
    Texture healthBarEnemyFull;
    if (!healthBarEnemyFull.loadFromFile("Enemy/healthFull.png"))
        return EXIT_FAILURE;


    Sprite bgSprite(bgTexture);
    Sprite healthPlayerEmpty(healthBarPlayerEmpty);
    Sprite healthPlayerFull(healthBarPlayerFull);
    Sprite healthEnemyEmpty(healthBarEnemyEmpty);
    Sprite healthEnemyFull(healthBarEnemyFull);

    healthEnemyEmpty.setPosition(Vector2f(1600 - 781, 0));
    healthEnemyFull.setPosition(Vector2f(1600 - 741, 0));

    Animation anRun(&runTexture, 6, 249, milliseconds(60), true);         //60
    Animation anIdle(&idleTexture, 2, 250, milliseconds(300), true);      //300
    Animation anCrouch(&crouchTexture, 1, 250, milliseconds(500), true);  //500
    Animation anJump(&jumpTexture, 2, 250, milliseconds(100), true);      //100
    Animation anFall(&fallTexture, 2, 250, milliseconds(200), true);      //200
    Animation annAtk(&nAtkTexture, 3, 400, milliseconds(60), true);       //60
    Animation andAtk(&dAtkTexture, 4, 350, milliseconds(100), true);      //100
    Animation anuAtk(&uAtkTexture, 4, 400, milliseconds(89), true);       //89
    Animation anHit(&hitTexture, 5, 300, milliseconds(100), true);        //100
    Animation anDie(&dyingTexture, 3, 475, milliseconds(350), false);

    Animation anRunEn(&runEnemyTexture, 6, 249, milliseconds(60), true);         //60
    Animation anIdleEn(&idleEnemyTexture, 2, 250, milliseconds(320), true);      //300
    Animation anCrouchEn(&crouchEnemyTexture, 1, 250, milliseconds(500), true);  //500
    Animation anJumpEn(&jumpEnemyTexture, 2, 250, milliseconds(100), true);      //100
    Animation anFallEn(&fallEnemyTexture, 2, 250, milliseconds(200), true);      //200
    Animation annAtkEn(&nAtkEnemyTexture, 3, 400, milliseconds(60), true);       //60
    Animation andAtkEn(&dAtkEnemyTexture, 4, 350, milliseconds(100), true);      //100
    Animation anuAtkEn(&uAtkEnemyTexture, 4, 400, milliseconds(89), true);       //89
    Animation anHitEn(&hitEnemyTexture, 5, 300, milliseconds(100), true);        //100
    Animation anDieEn(&dyingEnemyTexture, 3, 475, milliseconds(350), false);

    Character player("", &weaponTexture, &dyingEnemyTexture, Vector2f(0, 0));
    Character enemy(randint(0, 9) + "number" + randint(0, 9) + randint(0, 9) + randint(0, 9), &weaponTexture, &dyingEnemyTexture, Vector2f(1000, 500));;

    int gamestate = 0;  //0: menu
                        //1: show fighter
                        //2: gameplay
                        //3: play again?

    Clock clock;
    Time dt;
    Time totalTime = seconds(0);

    std::string enteredText;

    bool wasEnterPressed = false;
    bool wasYPressed = false;
    bool wasNPressed = false;
    int result = -1;    //-1: nothing
                        // 1: won
                        // 0: lost

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (gamestate == 0)
            {
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b' && enteredText.size() > 0)
                        enteredText.erase(enteredText.size() - 1, 1);
                    else if (event.text.unicode < 128 && enteredText.length() <= 455)
                    {
                        enteredText += static_cast<char>(event.text.unicode);
                    }
                    if (enteredText.length() % 38 == 0 && enteredText.length() != 0 && event.text.unicode != '\b')
                        enteredText += '&';
                }
            }
        }

        //       _  __       ___  __
        // |  | |_) | \  /\   |  |__
        // |__| |   |_/ /--\  |  |__
        dt = clock.restart();
        totalTime += dt;
        if (gamestate == 0)
        {
            if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            {
                enemy = Character(randint(0, 9) + "number" + randint(0, 9) + randint(0, 9) + randint(0, 9), &weaponTexture, &dyingEnemyTexture, Vector2f(1000, 500));;
                player = Character(enteredText, &weaponTexture, &dyingTexture, Vector2f(250, 500));
                std::cout << enteredText << "\n";
                gamestate = 1;
            }

            wasEnterPressed = Keyboard::isKeyPressed(Keyboard::Return);
        }
        if (gamestate == 1)
        {
            player.setPosition(Vector2f(1100, 372));

            if (!(Keyboard::isKeyPressed(Keyboard::Return)) && wasEnterPressed)
            {
                player.setPosition(Vector2f(250, 500));
                gamestate = 2;
            }

            wasEnterPressed = Keyboard::isKeyPressed(Keyboard::Return);
        }
        if (gamestate == 2)
        {
            player.update(dt, &annAtk, &andAtk, &anuAtk, &anHit, &anDie);
            enemy.AIupdate(dt, &annAtkEn, &andAtkEn, &anuAtkEn, &anHitEn, &anDieEn);
            player.checkHit(enemy.getHitbox(), enemy.getStrength());
            enemy.checkHit(player.getHitbox(), player.getStrength());

            if (enemy.getState() == STATE_DYING)
            {
                gamestate = 3;
                result = 1; //won
            }

            else if (player.getSpeed() == STATE_DYING)
            {
                gamestate = 3;
                result = 0; //lost
            }
        }
        if (gamestate == 3)
        {
            player.update(dt, &annAtk, &andAtk, &anuAtk, &anHit, &anDie);
            enemy.AIupdate(dt, &annAtkEn, &andAtkEn, &anuAtkEn, &anHitEn, &anDieEn);

            if (!(Keyboard::isKeyPressed(Keyboard::Y)) && wasYPressed)
            {
                gamestate = 0;
            }
            if (!(Keyboard::isKeyPressed(Keyboard::N)) && wasNPressed)
            {
                window.close();
            }

            wasYPressed = Keyboard::isKeyPressed(Keyboard::Y);
            wasNPressed = Keyboard::isKeyPressed(Keyboard::N);
        }

        //__   _                 .  _     __
        // | \ |_)  /\  \  /\  /  | | \ | /
        // |_/ |\  /--\  \/  \/   | |  \| \_]
        window.clear();
        window.draw(bgSprite);

        if (gamestate == 0)
        {
            drawString(&window, "enter the name of your fighter:", Vector2f(0, 40), &font);
            drawString(&window, enteredText, Vector2f(40, 100), &font);
            drawString(&window, "press enter to get started.", Vector2f(500, 794), &font);
        }
        if (gamestate == 1)
        {
            drawString(&window, "Strength:        %", Vector2f(25, 272), &font);
            drawString(&window, "Health:", Vector2f(25, 330), &font);
            drawString(&window, "Jump power:      %", Vector2f(25, 388), &font);
            drawString(&window, "Speed:           %", Vector2f(25, 446), &font);
            drawString(&window, "Weight:          Kg", Vector2f(25, 504), &font);

            drawFloat(&window, (int)(((float)player.getStrength() - 5) / 15 * 100), Vector2f(550, 272), &font);
            drawFloat(&window, (float)player.getMaxHealth(), Vector2f(550, 330), &font);
            drawFloat(&window, (int)(((float)player.getJump() - 12) / 16 * 100), Vector2f(550, 388), &font);
            drawFloat(&window, (int)(((float)player.getSpeed() - 75) / 45 * 100), Vector2f(550, 446), &font);
            drawFloat(&window, (float)player.getWeight(), Vector2f(550, 504), &font);

            player.draw(&window, dt, &anRun, &anIdle, &anCrouch, &anJump, &anFall, &annAtk, &andAtk, &anuAtk, &anHit, &anDie);

            if (enteredText.size() <= 42)
                drawString(&window, "Fighter: " + enteredText, Vector2f(0, 40), &font);
            else
                drawString(&window, "Fighter: The very long name you entered...", Vector2f(0, 40), &font);
            drawString(&window, "press enter to start", Vector2f(25, 736), &font);
        }
        if (gamestate == 2)
        {
            player.draw(&window, dt, &anRun, &anIdle, &anCrouch, &anJump, &anFall, &annAtk, &andAtk, &anuAtk, &anHit, &anDie);
            enemy.draw(&window, dt, &anRunEn, &anIdleEn, &anCrouchEn, &anJumpEn, &anFallEn, &annAtkEn, &andAtkEn, &anuAtkEn, &anHitEn, &anDieEn);

            healthPlayerFull.setTextureRect(IntRect(0, 0, 211 + ((float)player.getHealth() / player.getMaxHealth() * 530), 226));
            healthEnemyFull.setTextureRect(IntRect(530 - ((float)enemy.getHealth() / enemy.getMaxHealth() * 530), 0, ((float)enemy.getHealth() / enemy.getMaxHealth() * 530), 226));
            healthEnemyFull.setPosition(Vector2f(859 + 530 - ((float)enemy.getHealth() / enemy.getMaxHealth() * 530), 0));

            window.draw(healthPlayerEmpty);
            window.draw(healthPlayerFull);
            window.draw(healthEnemyEmpty);
            window.draw(healthEnemyFull);
        }
        if (gamestate == 3)
        {
            player.draw(&window, dt, &anRun, &anIdle, &anCrouch, &anJump, &anFall, &annAtk, &andAtk, &anuAtk, &anHit, &anDie);
            enemy.draw(&window, dt, &anRunEn, &anIdleEn, &anCrouchEn, &anJumpEn, &anFallEn, &annAtkEn, &andAtkEn, &anuAtkEn, &anHitEn, &anDieEn);

            window.draw(healthPlayerEmpty);
            window.draw(healthPlayerFull);
            window.draw(healthEnemyEmpty);
            window.draw(healthEnemyFull);

            if (result == 0)
                drawString(&window, "You lost...", Vector2f(525, 156), &font);
            else if (result == 1)
                drawString(&window, "You won!", Vector2f(525, 156), &font);

            drawString(&window, "Y: play again.", Vector2f(525, 214), &font);
            drawString(&window, "N: quit game.", Vector2f(525, 272), &font);
        }


        //DEBUG DRAWING
        //drawFloat(&window, gamestate, Vector2f(10, 260), &font);
        /*W
        drawFloat(&window, enemy.getHealth(), Vector2f(10, 190), &font);
        drawFloat(&window, enemy.getMaxHealth(), Vector2f(10, 260), &font);
        drawFloat(&window, (float)enemy.getHealth() / enemy.getMaxHealth() * 530, Vector2f(10, 310), &font);

        CircleShape circ(5);
        circ.setPosition(enemy.getPosition());
        circ.setFillColor(Color::Red);
        window.draw(circ);

        RectangleShape rect(Vector2f(player.getHitbox().width, player.getHitbox().height));
        rect.setFillColor(Color(255, 200, 0, 65));
        rect.setPosition(Vector2f(player.getHitbox().left, player.getHitbox().top));
        window.draw(rect);
        //*/

        window.display();


    }

    return 0;
}

int randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(value * clock());
    return value;
}

int randint(int low, int high, int seed)
{
    srand(seed);
    int value = rand() % (high + 1 - low) + low;
    return value;
}

int distance(float speed, float time)
{
    return (int)(time * speed);
}

void drawString(RenderWindow* window, std::string text, Vector2f position, Texture* fontTexture)
{
    int drawY = position.y;
    int drawX = position.x;

    for (int i = 0; i < text.length(); i++)
    {
        int num = (int)(text[i]);

        Sprite charSprite;
        charSprite.setTexture(*fontTexture);

        drawX += 38;

        if (num >= 48 && num <= 57)
            charSprite.setTextureRect(IntRect((num - 22) * 40, 0, 40, 69));
        else if (num >= 65 && num <= 90)
            charSprite.setTextureRect(IntRect((num - 65) * 40, 0, 40, 69));
        else if (num >= 97 && num <= 122)
            charSprite.setTextureRect(IntRect((num - 97) * 40, 0, 40, 69));
        else if (num == 46)
            charSprite.setTextureRect(IntRect(36 * 40, 0, 40, 69));
        else if (num == 58)
            charSprite.setTextureRect(IntRect(37 * 40, 0, 40, 69));
        else if (num == 44)
            charSprite.setTextureRect(IntRect(38 * 40, 0, 40, 69));
        else if (num == 37)
            charSprite.setTextureRect(IntRect(40 * 40, 0, 40, 69));
        else if (num == 33)
            charSprite.setTextureRect(IntRect(41 * 40, 0, 40, 69));
        else if (num == 38)
        {
            charSprite.setTextureRect(IntRect(39 * 40, 0, 40, 69));
            drawY += 58;
            drawX = position.x;
        }
        else
            charSprite.setTextureRect(IntRect(39 * 40, 0, 40, 69));

        charSprite.setPosition(Vector2f(drawX, drawY));
        window->draw(charSprite);
    }
}

void drawFloat(RenderWindow* window, float num, Vector2f position, Texture* fontTexture)
{
    std::string numStr;
    std::stringstream convert;
    convert << num;
    numStr = convert.str();

    drawString(window, numStr, position, fontTexture);
}
