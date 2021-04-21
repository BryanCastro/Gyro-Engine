#pragma once

class Animation{
    public:
        Animation();
        Animation(unsigned int index, unsigned int numFrames, unsigned int animationSpeed);
    
        unsigned int index;
        unsigned int numFrames;
        unsigned int animationSpeed;

    private:
};