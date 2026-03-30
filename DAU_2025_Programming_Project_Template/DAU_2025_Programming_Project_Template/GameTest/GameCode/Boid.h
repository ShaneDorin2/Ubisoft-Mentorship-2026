#pragma once

#include "EngineCode\Movable.h"
#include "app\app.h"
#include "EngineCode\Collider2D.h"
#include <memory> // unique_ptr<>  <-- Knows that it will always be the SOLE 'owner' of the referensed data. If the pointer is destroyed, the data is automatically destroyed as well (so no need for manual destruction.). 

class Boid : public Movable
{
public : // constructors

	Boid(float start_x_pos, float start_y_pos, CSimpleSprite* sprite, float start_x_velocity = 1, float start_y_velocity = 1);
	~Boid();

	// "rule of threes"
	Boid(const Boid&) = delete;
	Boid& operator=(const Boid&) = delete;

	Boid(Boid&&) noexcept = default; // required for vector<Boid>.reserve()

public : // logic
	
	void updateVelocity(float new_x, float new_y) { setVelocity(new_x, new_y); }
	void updatePosition(float& delta_time) override;

	void draw() { sprite->Draw(); } // TODO : make this into an Interface for all draw-able objects. //Drawable
	void drawGizmo();

public : // Get logic

	float getX() { return x_pos; }
	float getY() { return y_pos; }

	float getXVelocity() { return x_velocity; }
	float getYVelocity() { return y_velocity; }

	void setSpeed(float new_speed);

private : // logic
	void drawDirectionLine(float line_len);

private : // data
	std::unique_ptr<CSimpleSprite> sprite;
	std::unique_ptr<Collider2D> collider;
};

// so far, this is VERY similar to the Player class. 

