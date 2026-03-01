#pragma once

// Positionable class parents object that have a 2D postions. 

class Positionable
{
public: //contructors

	Positionable(float start_x = 0, float start_y = 0);

	// "rule of threes"
	Positionable(const Positionable&) = delete;
	Positionable& operator=(const Positionable&) = delete;

protected: //logic

	void setPosition(float new_x, float new_y);

protected: //memory

	float x_pos; 
	float y_pos;
};

