#include "stdafx.h"
#include "Boid.h"

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity, float start_y_velocity) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite)
{
	setVelocity(start_x_velocity, start_y_velocity);
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
	Movable::updatePosition(delta_time);
	sprite->SetPosition(x_pos, y_pos);
}

void Boid::draw()
{
	sprite->Draw();
}
