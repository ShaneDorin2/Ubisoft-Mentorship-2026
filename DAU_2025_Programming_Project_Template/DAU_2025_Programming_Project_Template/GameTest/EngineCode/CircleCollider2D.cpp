#include "stdafx.h"
#include "CircleCollider2D.h"
#include "App/app.h" // for DrawLine()


CircleCollider2D::CircleCollider2D(float radius, bool is_trigger, Positionable* parent, float x_pos, float y_pos):
	radius(radius), 
	Collider2D(CIRCLE, is_trigger, parent, x_pos, y_pos)
{}

CircleCollider2D::~CircleCollider2D()
{}

void CircleCollider2D::drawGizmo()
{
    drawCircle(getX(), getY(), radius, 15);
}

void CircleCollider2D::drawCircle(float x_center, float y_center, float radius, int num_of_sides)
{
    assert(num_of_sides > 0);

    float angleStep = 2.0f * PI / num_of_sides;

    for (int i = 0; i < num_of_sides; i++)
    {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        float x1 = x_center + cosf(angle1) * radius;
        float y1 = y_center + sinf(angle1) * radius;

        float x2 = x_center + cosf(angle2) * radius;
        float y2 = y_center + sinf(angle2) * radius;

        App::DrawLine(x1, y1, x2, y2, 1, 0, 0); // white by default. 
    }
    App::DrawLine(x_center, y_center, x_center + radius, y_center, 1, 0, 0);
}



