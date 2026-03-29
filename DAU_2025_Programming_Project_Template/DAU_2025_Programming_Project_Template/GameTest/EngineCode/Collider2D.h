#pragma once
#include "Positionable.h"
#include <vector>


enum eColliderShape
{
	CIRCLE,
	RECTANGLE
};

class Collider2D
{
public: // constructor

	Collider2D(eColliderShape shape, float radius, bool is_trigger = true, Positionable* parent = nullptr, float x_pos = NULL, float y_pos = NULL);
	~Collider2D();

	// "rule of threes"
	Collider2D(const Collider2D&) = delete;
	Collider2D& operator=(const Collider2D&) = delete;

public: // logic

	std::vector<Collider2D*> getAllCollitions();
	const eColliderShape& getShape() { return shape; }
	const float& getX() { return x_pos; }
	const float& getY() { return y_pos; }
	const float& getRadius() { return radius; }
	void setActive(bool is_active);
	void drawGizmo();

	void drawCircle(float x_center, float y_center, float radius, int num_of_sides); //TO DO, move this to another file where it can be used more widely. 

private: // logic

	bool compare2CircleCollitions(Collider2D* other_collider);

private: // data

	Positionable* parent;
	
	float x_pos;
	float y_pos;

	float radius;
	eColliderShape shape; // 16
	bool is_trigger; // 8
	bool has_parent; // 8

	bool is_active = true;
};

