#include "stdafx.h"
#include "RectangleCollider2D.h"
#include "App/app.h" // for DrawLine()

RectangleCollider2D::RectangleCollider2D(float width, float hight, bool is_trigger, Positionable* parent, float x_pos, float y_pos) :
	width(width), hight(hight),
	Collider2D(RECTANGLE, is_trigger, parent, x_pos, y_pos)
{}

RectangleCollider2D::~RectangleCollider2D()
{}

void RectangleCollider2D::drawGizmo()
{
	DrawSquare(getX(), getY(), getWidth(), getHight());
}

void RectangleCollider2D::DrawSquare(float x_center, float y_center, float width, float hight)
{
	App::DrawLine(	//left edge
		x_center - width / 2,
		y_center - hight / 2,
		x_center - width / 2,
		y_center + hight / 2,
		1, 0, 0);	
	
	App::DrawLine(	//bottom edge
		x_center - width / 2,
		y_center - hight / 2,
		x_center + width / 2,
		y_center - hight / 2,
		1, 0, 0);

	App::DrawLine(	//top edge
		x_center + width / 2,
		y_center + hight / 2,
		x_center - width / 2,
		y_center + hight / 2,
		1, 0, 0);

	App::DrawLine(	//right edge
		x_center + width / 2,
		y_center + hight / 2,
		x_center + width / 2,
		y_center - hight / 2,
		1, 0, 0);

	App::DrawLine( // center line
		x_center,
		y_center,
		x_center + width / 2,
		y_center,
		1, 0, 0);

}
