#include "stdafx.h"
#include "RayCastCollider2D.h"
#include "App/app.h" // for DrawLine()

RayCastCollider2D::RayCastCollider2D(float length, float direction_x, float direction_y, bool is_trigger, Positionable* parent, eTag tag, float x_pos, float y_pos):
	length(length), 
	direction_x(direction_x),
	direction_y(direction_y),
	Collider2D(RAYCAST, is_trigger, parent, tag, x_pos, y_pos)
{}

RayCastCollider2D::~RayCastCollider2D()
{}

void RayCastCollider2D::drawGizmo(float r, float g, float b)
{
	float end_point_x = getX() + length * direction_x;
	float end_point_y = getY() + length * direction_y;
	App::DrawLine(getX(), getY(), end_point_x, end_point_y, r, g, b);

}

void RayCastCollider2D::normalizeVector(float& x, float& y) // this same function exists in Movable. TODO: make this a more widely available function. 
{
	if (x == 0 && y == 0) return;

	// divide x and y by the magnitude (aka, the hypotinuse/distance)
	float magnitude = sqrtf(powf(abs(x), 2) + powf(abs(y), 2)); // pythagoras theorem 
	x /= magnitude;
	y /= magnitude;
}
