#pragma once
#include "EngineCode\Collider2D.h"

class RectangleCollider2D : public Collider2D
{
public: // contructor

	RectangleCollider2D(float width, float hight, bool is_trigger = true, Positionable* parent = nullptr, float x_pos = NULL, float y_pos = NULL);
	~RectangleCollider2D();

	// rule of "threes"
	RectangleCollider2D(const RectangleCollider2D&) = delete;
	RectangleCollider2D& operator=(const RectangleCollider2D&) = delete;

public: // logic

	const float& getWidth() { return width; }
	const float& getHight() { return hight; }

public: // override logic

	void drawGizmo(float r = 1, float g = 0, float b = 0) override;

private: // logic

	void DrawSquare(float x_center, float y_center, float width, float hight, float r = 1, float g = 0, float b = 0); //TO DO, move this to another file where it can be used more widely.

private: // data

	float width;
	float hight;
};

