#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
    public:
        Animation(Texture* _texture, int _frames, int _frameWidth, Time _frameTime, bool loop);
        int play(RenderWindow* window, Time dt, bool flipX);
        void setPosition(Vector2f val) { position = val; }
        void setFrame(int val) { currentFrame = val; }
        int getNextFrame() { return currentFrame + 1 >= frames ? 0 : currentFrame + 1; }
        int getCurrentFrame() { return currentFrame; }
        bool isAnimationOver() { return animationOver; }
    protected:
    private:
        Texture* texture;
        int frames;
        int frameWidth;
        int currentFrame;
        bool animationOver;
        bool loop;
        Time frameTime;
        Time sinceLastFrame;
        Vector2f position;
};

#endif // ANIMATION_H
