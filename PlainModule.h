#ifndef PLAIN_MODULE_H
#define PLAIN_MODULE_H

#include "Module.h"
#include "structs.h"
#include "bounceablePlane.h"

/** Simple module that has a single bouncable plane that fills the whole module's bounds
 */
class PlainModule : public Module
{
public:
    /** Method should be triggered when the ball enters the module
     *  Can be empty
     */
    void onBallEnter();

    /** Method should be triggered when the ball enters the exits
     *  Can be empty
     */
    void onBallExit();

    /** Method should be triggered every tick to display animations
     *  Can be empty
     */
    void animate();

    /** Method should be triggered every tick to the ball is in the module
     */
    void onTickInModule();

    /** Method should be triggered everytime the display() function in a freeglut program is called
     */
    void display();

private:
    BounceablePlane plane;
};

#endif
