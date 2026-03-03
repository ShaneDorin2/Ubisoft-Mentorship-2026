#pragma once

/* INPUT MANAGER
* 
* static class (meaning it does not need to be "constructed", correct ? It's more like a toolbox of functions.)
* 
* All user input is detected here. 
* When an input is detected, the appropriate event is called. 
*
*/

static class InputManager
{
public:
	static void processUserInput();
};

