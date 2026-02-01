#pragma once
#include "app\app.h"

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
	void setVelcity(float new_x, float new_y);
	void setPosition(float new_x, float new_y);

	void draw(); // TODO : make this into an Interface for all draw-able objects.

private:
	float x_pos;
	float y_pos;

	float x_velocity =0;
	float y_velocity =0;

	// should I make my SimpleSprite pointers inot uneaque_ptr ? 

	// this spright will be used in the absence of a provided spright refernece. 
	CSimpleSprite* default_sprite = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	
	CSimpleSprite* sprite;

	// helper functions 
	void normalizeVector(float& x, float& y);
};