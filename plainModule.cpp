/**
 * @todo: collision detection
 * @todo: physics of ball once collision detected - make ball bounce and multiply its velocity by a variable
 */

#include "PlainModule.h"
/** Sets the module's bounds, centre position and bounceable plane
 */
/*PlainModule::PlainModule(TwoDBounds boundSize, point3D newCentre, BounceablePlane p) {
    // todo: Call parent super-classconstructor somehow

    plane = p;
}*/

PlainModule::~PlainModule() {

}

/** Method should be triggered when the ball enters the module
 *  Can be empty
 */
void PlainModule::onBallEnter() {

}

/** Method should be triggered when the ball enters the exits
 *  Can be empty
 */
void PlainModule::onBallExit() {

}

/** Method should be triggered every tick to display animations
 *  Can be empty
 */
void PlainModule::animate() {

}

/** Method should be triggered every tick to the ball is in the module
 */
void PlainModule::onTickInModule() {

}

/** Method should be triggered everytime the display() function in a freeglut program is called
 */
void PlainModule::display() {

}
