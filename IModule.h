/** Interface for modules
 *	@todo: improve design
 *	@todo: replace pseudocode with c++
 *
 */
#include "GlobalVariablesAndStructs.h"

Interface IModule
{
	//Constructor
	Module(3dPoint pos)
	{
		//Set bounds around pos
		//todo: implement
	}
	/* Defining bounds for the module, assuming the centre is the origin
	 * note that it doesn't take into account height, so modules can't be stacked
	 */
	Bounds default_bounds
	
	/* Defining bounds for the module, assuming the centre is the origin
	 * note that it doesn't take into account height, so modules can't be stacked
	 */
	Bounds bounds
	
	//Set the centre position of the module
	3dPoint pos
	
	//What happens when the ball enters the module
	virtual void onBallEnter()
	
	//What happens when the ball exists the module
	virtual void onBallExit()
	
	//animations to be done every tick, regardless of where the ball is
	virtual void animate()
	
	//What the module should do each tick when the ball is in the module
	virtual void onTickInModule()
	
	//Displays non-moving objects
	virtual void display()
}
