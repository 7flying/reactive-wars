#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimationHandler.hpp"


Animation::Animation(unsigned int startFrame, unsigned int endFrame,
                     float duration)
{
    this->startFrame = startFrame;
    this->endFrame = endFrame;
    this->duration = duration;
}

AnimationHandler::AnimationHandler()
{
    this->time = 0.0f;
    this->currentAnim = -1;
}

AnimationHandler::AnimationHandler(const IntRect &frameSize)
{
    this->frameSize = frameSize;
    this->time = 0.0f;
    this->currentAnim = -1;
}

void AnimationHandler::addAnim(Animation &anim)
{
    this->animations.push_back(anim);
}

void AnimationHandler::update(const float dt)
{
    if (this->currentAnim >= (int) this->animations.size()
        || this->currentAnim < 0)
        return;
    float duration = this->animations[this->currentAnim].duration;
    // Check if the animation has progressed to a new frame
    // -> change to next frame
    if (int((this->time + dt) / duration) > int(this->time / duration)) {
        // Get frame number
        int frame = int((this->time + dt) / duration);
        // adjust for loop
        frame %= this->animations[this->currentAnim].getLength();

        // Set sprite to new frame
        IntRect rect = this->frameSize;
        rect.left = rect.width * frame;
        rect.top = rect.height * this->currentAnim;
        this->bounds = rect;
    }
    // increment the time elapsed
    this->time += dt;
    // adjust for loop
    if (this->time > duration * this->animations[this->currentAnim].getLength())
        this->time = 0.0f;
}

void AnimationHandler::changeAnim(unsigned int animID)
{
    // do not change animation if it is currectly active or the new one does
    // not exist
    if (this->currentAnim == (int) animID || animID >= this->animations.size())
        return;
    this->currentAnim = animID;
    // update animation bounds
    IntRect rect = this->frameSize;
    rect.top = rect.height * animID;
    this->bounds = rect;
    this->time = 0.0f;
}
