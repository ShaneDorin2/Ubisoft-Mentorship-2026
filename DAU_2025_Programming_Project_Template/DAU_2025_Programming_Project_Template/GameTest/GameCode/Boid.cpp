#include "stdafx.h"
#include "Boid.h"

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity, float start_y_velocity) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite),
	circle_collider(new CircleCollider2D(10, true, this)),
	raycast_collider(new RayCastCollider2D(100, 1, 1, true, this))
{
	assert(sprite != nullptr);
	
	setVelocity(start_x_velocity, start_y_velocity);
	Movable::setSpeed(0.08f);
	sprite->SetScale(0.5f);

	circle_collider->setActive(false);
}

Boid::~Boid()
{}

void Boid::updateVelocity(float new_x, float new_y)
{
	setVelocity(new_x, new_y);
	raycast_collider->setDirection(new_x, new_y);
}

void Boid::updatePosition(float& delta_time)
{
	Movable::updatePosition(delta_time);
	sprite->SetPosition(x_pos, y_pos);
}

void Boid::drawGizmo()
{
	raycast_collider->drawGizmo();
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
