#pragma once
#include "app\app.h"
#include "functional"
#include "EngineCode\Movable.h"
#include "EngineCode\Collider2D.h"
#include <memory>

/*
* This class handles the player character's Position, Movement and Appearance. 
* inputs:
*	- verical & horisontal direction (via events)
*
* 
* TO DO:
*	- Make it inherit a Drawable Interface containting the draw() function.
*	- Add sprite_offset_x/y float variables that determin the position of the sprite relative to the Player's position. 
*	- Draw a Gizmo indicating the point coordinate of the Player. (Use App::DrawLine())
*/

class Player : public Movable
{
public: // constructor

	Player(float start_x_pos, float start_y_pos, CSimpleSprite* sprite_ptr);
	~Player();

	// "rule of threes"
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

public: // logic

	void updateLogic(); 
	void updatePosition(float& delta_time) override;

	void draw() { sprite->Draw(); } // TODO : make this into an Interface for all draw-able objects. //Drawable

private: // logic

	// Event subscribers
	void onUpInput() { in_direction_input_y -= 1; }
	void onDownInput() { in_direction_input_y += 1; }
	void onRightInput() { in_direction_input_x += 1; }
	void onLeftInput() { in_direction_input_x -= 1; }

private: // memeory

	std::unique_ptr<CSimpleSprite> sprite; 
	std::unique_ptr<Collider2D> collider;

private: // input memory

	// "in_" means that these are values that 'come from' outside of the class. 
	// in this case, they are modified by the user input event subscribers. 
	float in_direction_input_x = 0; 
	float in_direction_input_y = 0;

	// Event subscribers -- Player
	std::function<void()> onUpInputLambda; // i KINDA remember how lambda's work. 
	std::function<void()> onDownInputLambda;
	std::function<void()> onRightInputLambda;
	std::function<void()> onLeftInputLambda;

};