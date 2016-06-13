#ifndef ANIMATION_HANDLER_HPP
#define ANIMATION_HANDLER_HPP

#include <SFML/Graphics.hpp>
#include <vector>


using namespace std;
using namespace sf;

class Animation {
public:
    unsigned int startFrame, endFrame;
    float duration;

    Animation(unsigned int startFrame, unsigned int endFrame, float duration);
    unsigned int getLength() { return endFrame - startFrame + 1; }
};

class AnimationHandler {
private:
    vector<Animation> animations;
    /** Current time since the animation started**/
    float time;
    /** Vertical index in the grid or the horizontal index in vector to keep
      * track of which animation is running **/
    int currentAnim;

public:
    /* Current section of the texture that should be displayed */
    IntRect bounds; // Rectangle with integers for start coord, width and height
    /* Pixel dimensions of each individual frame */
    IntRect frameSize;

    AnimationHandler();
    AnimationHandler(const IntRect &frameSize);
    
    
    /** Adds a new animation **/
    void addAnim(Animation &anim);

    /** Update the current frame of animation. dt (delta time) is the time
      * since the update was last called -> time for one frame to be executed */
    void update(const float dt);

    /* Change the animation, resetting time in the process */
    void changeAnim(unsigned int animNum);
};

#endif // ANIMATION_HANDLER_HPP
