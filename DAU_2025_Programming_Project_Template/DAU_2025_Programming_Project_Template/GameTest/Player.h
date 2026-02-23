#pragma once
#include "app\app.h"
#include "functional"

/*
* This class handles the player character's Position, Movement and Appearance. 
* 
* TO DO:
*	- Make it inherit from a Transformable Parent-Class (that handles position, rotation and scale). 
*	- Make it inherit a Drawable Interface containting the draw() function.
*	- Add sprite_offset_x/y float variables that determin the position of the sprite relative to the Player's position. 
*	- Draw a Gizmo indicating the point coordinate of the Player. (Use App::DrawLine())
*/


class Player
{

public:
	// constructor 
	Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr = nullptr);
	~Player();
	// "rule of threes"
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;


	// transform
	// should I create a Transform-able parent class objects with positions, scales and rotations ? 
	void updatePosition(float& deltaTime);
	void updateVelcity();
	void setVelcity(float new_x, float new_y);
	void setPosition(float new_x, float new_y);

	void draw(); // TODO : make this into an Interface for all draw-able objects.

private:
	void normalizeVector(float& x, float& y);

	void onUpInput();
	void onDownInput();
	void onRightInput();
	void onLeftInput();

	// should I make my SimpleSprite pointers inot uneaque_ptr ? 

	// this spright will be used in the absence of a provided spright refernece. 

	// helper functions 

	// -----------------------------------------------------------------------------------------
	// directional input
	// can come from user controls or scripted movements. 

	// "in_" means that these are values that 'come from' outside of the class. 
	// in this case, they are modified by the user input event subscribers. 

private:
	CSimpleSprite* default_sprite;
	CSimpleSprite* sprite;

	float in_direction_input_x = 0;
	float in_direction_input_y = 0;

	float x_pos;
	float y_pos;

	float x_velocity = 0;
	float y_velocity = 0;

	// Event subscribers
	std::function<void()> onDownInputLambda;
	std::function<void()> onUpInputLambda; // i KINDA remember how lambda's work. 
	std::function<void()> onRightInputLambda;
	std::function<void()> onLeftInputLambda;
};