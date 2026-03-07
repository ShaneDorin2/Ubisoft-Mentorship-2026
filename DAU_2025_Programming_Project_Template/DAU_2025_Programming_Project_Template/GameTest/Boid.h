#pragma once

#include "Movable.h"
#include "app\app.h"

class Boid : public Movable
{
public : // constructors

	Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity = 1, float start_y_velocity = 1);
	~Boid();

	// "rule of threes"
	Boid(const Boid&) = delete;
	Boid& operator=(const Boid&) = delete;

public : // logic
	
	void updateVelocity();
	void updatePosition(float& delta_time) override;

	void draw(); // TODO : make this into an Interface for all draw-able objects. //Drawable

private : // data
	CSimpleSprite* sprite;
};

// so far, this is VERY similar to the Player class. 

