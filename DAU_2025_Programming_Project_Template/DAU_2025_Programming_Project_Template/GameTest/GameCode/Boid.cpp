#include "stdafx.h"
#include "Boid.h"
#include <EngineCode/CollisionDetection.h>

Boid::Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity, float start_y_velocity) :
	Movable(start_x_pos, start_y_pos),
	sprite(sprite),
	circle_collider(new CircleCollider2D(2, true, this, ANGEL)),
	raycast_collider_12(new RayCastCollider2D(20, 1, 1, true, this)),
	raycast_collider_3(new RayCastCollider2D(20, 1, 1, true, this))
{
	assert(sprite != nullptr);
	
	setVelocity(start_x_velocity, start_y_velocity);
	Movable::setSpeed(0.08f);
	sprite->SetScale(0.5f);

	circle_collider->setActive(true);
}

Boid::~Boid()
{}

void Boid::updateVelocity(float new_x, float new_y)
{
	float wall_avoidance_weight = 0.5;
	
	raycast_collider_12->setDirection(new_x, new_y);
	raycast_collider_3->setDirection(new_y, -new_x);

	std::vector<Collider2D*> collisions = CollisionDetection::getAllCollitions(*raycast_collider_12, false);
	if (collisions.empty() == false) {
		collisions = CollisionDetection::getAllCollitions(*raycast_collider_3, false);
		if (collisions.empty() == false) {
			new_x -= new_y * wall_avoidance_weight;
			new_y += new_x * wall_avoidance_weight;
		}
		else 
		{
			new_x += new_y * wall_avoidance_weight;
			new_y -= new_x * wall_avoidance_weight;
		}
	}

	setVelocity(new_x, new_y);
}

void Boid::updatePosition(float& delta_time)
{
	Movable::updatePosition(delta_time);
	sprite->SetPosition(x_pos, y_pos);
}

void Boid::drawGizmo()
{
	circle_collider->drawGizmo();
	raycast_collider_12->drawGizmo();
	raycast_collider_3->drawGizmo(0, 1, 0);
}

void Boid::setSpeed(float new_speed)
{
	assert(new_speed >= 0);
	Movable::setSpeed(new_speed);
}
