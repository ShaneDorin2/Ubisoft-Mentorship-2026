#pragma once
#include "app\app.h"
#include "functional"
#include "Movable.h"

/*
* This class handles the player character's Position, Movement and Appearance. 
* 
* TO DO:
*	- Make it inherit a Drawable Interface containting the draw() function.
*	- Add sprite_offset_x/y float variables that determin the position of the sprite relative to the Player's position. 
*	- Draw a Gizmo indicating the point coordinate of the Player. (Use App::DrawLine())
*/

class Player : public Movable
{
public:
	// constructor 
	Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr = nullptr);
	~Player();

	// "rule of threes"
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;


	// transform
	void updateVelocity(); //player
	void updatePosition(float& delta_time) override;

	void draw(); // TODO : make this into an Interface for all draw-able objects. //Drawable

private: // logic


	// Event subscribers
	void onUpInput(); //Player
	void onDownInput(); //Player
	void onRightInput(); //Player
	void onLeftInput(); //Player

private: // memeory

	// this spright will be used in the absence of a provided spright refernece. 
	CSimpleSprite* sprite; //Drawable

private: // directional input memory
	// can come from user controls or scripted movements. 

	// "in_" means that these are values that 'come from' outside of the class. 
	// in this case, they are modified by the user input event subscribers. 
	float in_direction_input_x = 0; // Player
	float in_direction_input_y = 0;

	// Event subscribers -- Player
	std::function<void()> onUpInputLambda; // i KINDA remember how lambda's work. 
	std::function<void()> onDownInputLambda;
	std::function<void()> onRightInputLambda;
	std::function<void()> onLeftInputLambda;

};