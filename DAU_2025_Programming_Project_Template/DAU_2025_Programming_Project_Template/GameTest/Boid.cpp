#include "stdafx.h"
#include "Boid.h"

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity, float start_y_velocity) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite)
{
	assert(sprite != nullptr);
	
	setVelocity(start_x_velocity, start_y_velocity);
	Movable::setSpeed(0.08);
	sprite->SetScale(0.1);

	collider = new Collider2D(CIRCLE, 1, true, this);
	//collider->setActive(false);
}

Boid::~Boid()
{
	delete sprite;
	delete collider;
}

void Boid::updateVelocity(float new_x, float new_y)
{
	setVelocity(new_x, new_y);
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

float Boid::getX()
{
	return x_pos;
}

float Boid::getY()
{
	return y_pos;
}

float Boid::getXVelocity()
{
	return x_velocity;
}

float Boid::getYVelocity()
{
	return y_velocity;
}

void Boid::setSpeed(float new_speed)
{
	assert(new_speed >= 0);
	Movable::setSpeed(new_speed);
}
