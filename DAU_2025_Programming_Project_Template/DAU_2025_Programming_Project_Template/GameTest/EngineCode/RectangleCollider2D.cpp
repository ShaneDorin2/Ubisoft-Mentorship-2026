#include "stdafx.h"
#include "RectangleCollider2D.h"

RectangleCollider2D::RectangleCollider2D(float width, float hight, bool is_trigger, Positionable* parent, float x_pos, float y_pos) :
	width(width), hight(hight),
	Collider2D(RECTANGLE, is_trigger, parent, x_pos, y_pos)
{}

RectangleCollider2D::~RectangleCollider2D()
{}

void RectangleCollider2D::drawGizmo()
{
}

void RectangleCollider2D::DrawSquare(float x_center, float y_center, float width, float hight, int num_of_sides)
{
}
