#pragma once
#include "EngineCode\Collider2D.h"

class CircleCollider2D : public Collider2D
{
public : // contructor

	CircleCollider2D(float radius, bool is_trigger = true, Positionable* parent = nullptr, float x_pos = NULL, float y_pos = NULL);
	~CircleCollider2D();

	// rule of "threes"
	CircleCollider2D(const CircleCollider2D&) = delete;
	CircleCollider2D& operator=(const CircleCollider2D&) = delete;

public : // logic
	
	const float& getRadius() { return radius; }

public : // override logic

	bool isCollidingWith(Collider2D* other_collider) override;
	void drawGizmo() override;

private : // logic
	
	void drawCircle(float x_center, float y_center, float radius, int num_of_sides); //TO DO, move this to another file where it can be used more widely.

private : // data

	float radius;
};

