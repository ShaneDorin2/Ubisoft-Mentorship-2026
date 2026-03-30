#include "stdafx.h"
#include "Boid.h"

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity, float start_y_velocity) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite),
	collider(new Collider2D(CIRCLE, 10, true, this))
{
	assert(sprite != nullptr);
	
	setVelocity(start_x_velocity, start_y_velocity);
	Movable::setSpeed(0.08f);
	sprite->SetScale(0.1f);

	collider->setActive(false);
}

Boid::~Boid()
{}

void Boid::updatePosition(float& delta_time)
{
	Movable::updatePosition(delta_time);
	sprite->SetPosition(x_pos, y_pos);
}

void Boid::drawGizmo()
{
	drawDirectionLine(100);
}

void Boid::setSpeed(float new_speed)
{
	assert(new_speed >= 0);
	Movable::setSpeed(new_speed);
}

void Boid::drawDirectionLine(float line_len)
{
	App::DrawLine(
		x_pos, y_pos, 
		x_pos + x_velocity *line_len, 
		y_pos + y_velocity *line_len, 
		0, 0, 1);
}
