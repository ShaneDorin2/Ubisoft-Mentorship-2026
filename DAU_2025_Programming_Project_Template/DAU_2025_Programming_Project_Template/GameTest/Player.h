#pragma once
#include "app\app.h"

class Player
{
public:
	// constructor 
	Player(float start_x_pos, float start_y_pos);

	// sprite handling 
	CSimpleSprite* sprite;

	// transform
	void updatePosition(float& deltaTime);
	void setVelcity(float new_x, float new_y);
	void setPosition(float new_x, float new_y);

private:
	float x_pos;
	float y_pos;

	float x_velocity;
	float y_velocity;
};