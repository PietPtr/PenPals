#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Animation;

using namespace sf;

enum State
{
    STATE_STANDING,
    STATE_WALKING_LEFT,
    STATE_WALKING_RIGHT,
    STATE_CROUCHING,
    STATE_JUMPING,
    STATE_FALLING,
    STATE_NEUTRALATTACK,
    STATE_UPATTACK,
    STATE_DOWNATTACK,
    STATE_HIT,
    STATE_DYING,
};

enum Weapon
{
    WEAPON_GPU,      //
    WEAPON_PENCIL,   //
    WEAPON_SWORD,    //
    WEAPON_KEYBOARD, //
    WEAPON_TREE,     //
    WEAPON_TRAIN,    //
    WEAPON_WINDMILL  //
};

enum Input
{
    INPUT_NONE,
    INPUT_W,
    INPUT_A,
    INPUT_S,
    INPUT_D,
    INPUT_SPACE,
    INPUT_ENTER
};

enum Direction
{
    RIGHT,
    LEFT
};

class Character
{
    public:
        Character(std::string name, Texture* weaponTexture, Texture* dyingTexture, Vector2f position);
        void draw(RenderWindow* window, Time dt, Animation* anRun, Animation* anIdle, Animation* anCrouch, Animation* anJump,
                                                 Animation* anFall, Animation* annAtk, Animation* andAtk, Animation* anuAtk,
                                                 Animation* anHit, Animation* anDie);
        void update(Time dt, Animation* annAtk, Animation* andAtk, Animation* anuAtk, Animation* anHit, Animation* anDie, Input input, Input input2);
        void drawWeapon(RenderWindow* window, Vector2f weaponPos, Vector2f weaponFlipPos, float weaponRotation);
        void AIupdate(Time dt, Animation* annAtkEn, Animation* andAtkEn, Animation* anuAtkEn, Animation* anHitEn, Animation* anDieEn);
        int getHealth() { return health; }
        int getMaxHealth() {return maxHealth; }
        int getStrength() { return strength; }
        int getJump() { return jump; }
        int getWeight() { return weight; }
        int getSpeed() { return speed; }
        Vector2f getPosition() { return position; }
        void setPosition(Vector2f val) { position = val; }
        IntRect getHitbox() { return hitbox; }
        bool checkHit(IntRect hitbox, int enemyStrength);
        bool getFlip() { return flip; }
        State getState() { return state; }
    protected:
    private:
        int health;
        int maxHealth;
        int weight;
        int strength;
        int jump;
        int speed;
        Weapon weapon;
        Vector2f velocity;
        Vector2f position;
        State state;
        State graphicState;
        bool flip; //False: faces right (D), True: faces left (A)
        Texture* weaponTexture;
        Texture* deadTexture;
        IntRect hitbox; //This is the hitbox of the weapon. all values are zero when not attacking
        bool wasEnterPressed;
        bool isHit;
        Time totalTime;
        Time lastHit;
};

#endif // CHARACTER_H
