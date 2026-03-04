#pragma once

#include "Movable.h"
#include "app\app.h"

class Boid : public Movable
{
public : // constructors

	Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite);
	~Boid();

	// "rule of threes"
	Boid(const Boid&) = delete;
	Boid& operator=(const Boid&) = delete;

public : // logic
	
	void updateVelocity();
	void updatePosition(float& delta_time) override;

	void draw(); // TODO : make this into an Interface for all draw-able objects. //Drawable

	void setSeparationTarget(float x, float y);
	void setAlignmentTarget(float x, float y);
	void setCohesionTarget(float x, float y);

	void setWeights(short separation, short alignment, short coheshion);

private : // data
	CSimpleSprite* sprite;

	float in_separation_target_x;
	float in_separation_target_y;

	float in_alignment_target_x;
	float in_alignment_target_y;

	float in_cohesion_target_x;
	float in_cohesion_target_y;

	short separation_weight;
	short alignment_weight;
	short cohesion_weight;
	// made these shorts to avoid buffer space. 
};

