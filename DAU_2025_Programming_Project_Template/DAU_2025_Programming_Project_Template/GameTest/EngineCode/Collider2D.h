#pragma once
#include "Positionable.h"
#include <vector>

enum eColliderShape //MUST MATCH SUB-CLASS TYPE
{
	CIRCLE,
	RECTANGLE
};

class Collider2D
{
public: // logic

	void setActive(bool is_active);
	const bool& getActive() { return is_active; }
	const float& getX() { return has_parent ? parent->getXPos() : x_pos; }
	const float& getY() { return has_parent ? parent->getYPos() : y_pos; }
	const eColliderShape& getShape() { return shape; }

public: // virtual logic

	virtual void drawGizmo() = 0;

protected: // constructor

	Collider2D(eColliderShape shape, bool is_trigger = true, Positionable* parent = nullptr, float x_pos = NULL, float y_pos = NULL);
	~Collider2D();

	// "rule of threes"
	Collider2D(const Collider2D&) = delete;
	Collider2D& operator=(const Collider2D&) = delete;

private: // data

	Positionable* parent;
	
	float x_pos;
	float y_pos;

	eColliderShape shape; //32
	bool is_trigger; // 8
	bool has_parent; // 8
	bool is_active = true; // 8
	
};

