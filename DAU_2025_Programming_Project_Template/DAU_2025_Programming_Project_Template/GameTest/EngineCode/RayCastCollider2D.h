#pragma once
#include "EngineCode\Collider2D.h"

class RayCastCollider2D : public Collider2D
{

public: //contructor

	RayCastCollider2D(float length, float direction_x, float direction_y, bool is_trigger = true, Positionable* parent = nullptr, float x_pos = NULL, float y_pos = NULL);
	~RayCastCollider2D();

	// rule of "threes"
	RayCastCollider2D(const RayCastCollider2D&) = delete;
	RayCastCollider2D& operator = (const RayCastCollider2D) = delete;

public: // logic

	const float& getLength() { return length; }
	const float& getDirectionX() { return direction_x; }
	const float& getDirectionY() { return direction_y; }

	void setDirection(float x, float y) { direction_x = x; direction_y = y; }

public: // override logic

	void drawGizmo() override;

private: 

	void normalizeVector(float& x, float& y);

private: // data

	float length;
	float direction_x;
	float direction_y;
};

