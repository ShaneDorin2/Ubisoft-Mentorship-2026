#pragma once

/* SceneMember is an interface (abstract class) required for any object that can be loaded into a Scene. 
* All logic and data names start with scene. 
* 
* TO DO: Make a Scene class. 
*/

class SceneMember
{
public: // virtual logic
	//virtual std::unique_ptr <SceneMember> sceneCreateInstance(float x_pos, float y_pos) = 0; 
	// // would like it if this worked, but I can't make static virtual functions. I also can't return an abstract class. 
	// // Also no virtual constructors. [cries] I will just need to TRUST that all SceneMembers have a public constructor. 

	virtual ~SceneMember() = default;
	virtual void sceneUpdateLogic(float delta_time) = 0;
	virtual void sceneDraw() = 0;
	virtual void sceneDrawGizmos() = 0;

public: // logic
	bool scene_is_active = true;
};

