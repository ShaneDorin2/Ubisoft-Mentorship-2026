#include "stdafx.h"
#include "Boid.h"

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite)
{
}

Boid::~Boid()
{
	delete sprite;
}

void Boid::updateVelocity()
{

}

void Boid::updatePosition(float& delta_time)
{
	Movable::updatePosition;
	sprite->SetPosition(x_pos, y_pos);
}

void Boid::draw()
{
	sprite->Draw();
}

void Boid::setSeparationTarget(float x, float y) 
{
	in_separation_target_x = x;
	in_separation_target_y = y;
}

void Boid::setAlignmentTarget(float x, float y)
{
	in_alignment_target_x = x;
	in_alignment_target_y = y;
}

void Boid::setCohesionTarget(float x, float y)
{
	in_cohesion_target_x = x;
	in_cohesion_target_y = y;
}

void Boid::setWeights(short separation, short alignment, short coheshion)
{
	separation_weight = separation;
	alignment_weight = alignment;
	cohesion_weight = coheshion;
}
