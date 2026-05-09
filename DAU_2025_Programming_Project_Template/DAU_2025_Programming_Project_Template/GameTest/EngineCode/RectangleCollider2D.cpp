#include "stdafx.h"
#include "RectangleCollider2D.h"
#include "App/app.h" // for DrawLine()

RectangleCollider2D::RectangleCollider2D(float width, float hight, bool is_trigger, Positionable* parent, float x_pos, float y_pos) :
	width(width), hight(hight),
	Collider2D(RECTANGLE, is_trigger, parent, x_pos, y_pos)
{}

RectangleCollider2D::~RectangleCollider2D()
{}

void RectangleCollider2D::drawGizmo(float r, float g, float b)
{
	DrawSquare(getX(), getY(), getWidth(), getHight(), r, g, b);
}

void RectangleCollider2D::DrawSquare(float x_center, float y_center, float width, float hight, float r, float g, float b)
{
	App::DrawLine(	//left edge
		x_center - width / 2,
		y_center - hight / 2,
		x_center - width / 2,
		y_center + hight / 2,
		r, g, b);	
	
	App::DrawLine(	//bottom edge
		x_center - width / 2,
		y_center - hight / 2,
		x_center + width / 2,
		y_center - hight / 2,
		r, g, b);

	App::DrawLine(	//top edge
		x_center + width / 2,
		y_center + hight / 2,
		x_center - width / 2,
		y_center + hight / 2,
		r, g, b);

	App::DrawLine(	//right edge
		x_center + width / 2,
		y_center + hight / 2,
		x_center + width / 2,
		y_center - hight / 2,
		r, g, b);

	App::DrawLine( // center line
		x_center,
		y_center,
		x_center + width / 2,
		y_center,
		r, g, b);
}
