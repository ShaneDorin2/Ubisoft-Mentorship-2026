#pragma once

/* SceneMember is an interface (abstract class) required for any object that can be loaded into a Scene. 
* All logic and data names start with scene. 
* 
* TO DO: Make a Scene class. 
*/

class SceneMember
{
public: // virtual logic
	virtual SceneMember sceneCreateInstance(float x_pos, float y_pos) = 0;
	virtual void sceneUpdateLogic(float delta_time) = 0;
	virtual void sceneDraw() = 0;
	virtual void sceneDrawGizmo() = 0;

public: // logic
	bool scene_is_active = true;
};

