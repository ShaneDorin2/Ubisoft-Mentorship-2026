#include "stdafx.h"
#include "Movable.h"
#include <cmath>

void Movable::updatePosition(float& delta_time)
{
	x_pos += x_velocity * delta_time;
	y_pos += y_velocity * delta_time;
}

Movable::Movable(float start_x_pos, float start_y_pos):
Positionable(start_x_pos, start_y_pos)
{}

void Movable::setVelocity(float new_x, float new_y)
{
	x_velocity = new_x;
	y_velocity = new_y;
	normalizeVector(x_velocity, y_velocity);
}

void Movable::normalizeVector(float& x, float& y)
{
	if (x == 0 && y == 0) return;

	// divide x and y by the magnitude (aka, the hypotinuse/distance)
	float magnitude = sqrtf(powf(abs(x), 2) + powf(abs(y), 2)); // pythagoras theorem 
	x /= magnitude;
	y /= magnitude;
}
