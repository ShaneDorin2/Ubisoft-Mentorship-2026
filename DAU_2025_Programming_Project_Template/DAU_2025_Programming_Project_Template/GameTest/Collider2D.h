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
	const eColliderShape& getShape();
	const float& getX();
	const float& getY();
	const float& getRadius();
	void setActive(bool is_active);

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

