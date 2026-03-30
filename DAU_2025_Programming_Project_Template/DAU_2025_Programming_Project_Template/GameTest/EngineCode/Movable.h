#pragma once
#include "Positionable.h"

// Moveable: Base class for objects that "move" (theu 2D positions change over time). 

/*
* TO DO:
* allow for the handling of Skacle and Rotation. 
*/

class Movable : public Positionable
{
public : // logic

	virtual void updatePosition(float& delta_time);

protected : // constructor 

	Movable(float start_x_pos = 0, float start_y_pos = 0);

	// "rule of threes"
	Movable(const Movable&) = delete;
	Movable& operator=(const Movable&) = delete;

	Movable(Movable&&) noexcept = default; // required for vector<Boid>.reserve()

protected : // logic

	void setVelocity(float new_x, float new_y);
	void setSpeed(float new_speed) { speed = new_speed; }

protected: // memory

	float x_velocity = 0; 
	float y_velocity = 0;

	float speed = 1;
	// buffer be here :(

private : // logic

	void normalizeVector(float& x, float& y);
	void wrapCoordinates(float& x, float& y);
};

