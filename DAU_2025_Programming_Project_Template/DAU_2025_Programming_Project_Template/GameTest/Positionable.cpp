#include "stdafx.h"
#include "Positionable.h"

Positionable::Positionable(float start_x, float start_y) :
	x_pos(start_x), y_pos(start_y)
{}

void Positionable::setPosition(float new_x, float new_y)
{
	x_pos = new_x;
	y_pos = new_y;
}
