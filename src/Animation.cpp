#include <iostream>
#include "Animation.h"

using namespace sf;
Animation::Animation(Texture* _texture, int _frames, int _frameWidth, Time _frameTime, bool _loop)
{
    texture = _texture;
    frames = _frames;
    frameWidth = _frameWidth;
    currentFrame = 0;
    frameTime = _frameTime;
    sinceLastFrame = milliseconds(0);
    position = Vector2f(0, 0);
    animationOver = false;
    loop = _loop;
}

int Animation::play(RenderWindow* window, Time dt, bool flipX)
{
    animationOver = false;
    sinceLastFrame += dt;

    Sprite sprite;
    sprite.setTexture(*texture);
    sprite.setOrigin(frameWidth / 2.0, texture->getSize().y / 2.0);
    sprite.setPosition(position);
    sprite.setTextureRect(IntRect(frameWidth * currentFrame, 0, frameWidth, texture->getSize().y));

    if (flipX)
    {
        sprite.scale(-1.0, 1.0);
    }

    window->draw(sprite);

    if (sinceLastFrame >= frameTime)
    {
        sinceLastFrame = milliseconds(0);
        currentFrame++;
    }
    if (currentFrame >= frames)
    {
        if (loop)
            currentFrame = 0;
        else
            currentFrame = frames - 1;
        animationOver = true;
    }

    return currentFrame;
}
