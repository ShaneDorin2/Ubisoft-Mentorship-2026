#pragma once

// Positionable: Base class for objects that have a 2D position. 

class Positionable
{
public : // logic

	const float& getXPos() { return x_pos; }
	const float& getYPos() { return y_pos; }

protected: //contructors

	Positionable(float start_x = 0, float start_y = 0);

	// "rule of threes"
	Positionable(const Positionable&) = delete;
	Positionable& operator=(const Positionable&) = delete;

	Positionable(Positionable&&) noexcept = default; // required for vector<Boid>.reserve()

protected: //logic

	void setPosition(float new_x, float new_y);

protected: //memory

	float x_pos; 
	float y_pos;
};

