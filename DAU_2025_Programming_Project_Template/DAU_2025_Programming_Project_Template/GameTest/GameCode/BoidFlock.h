#pragma once
#include <vector>
#include "Boid.h"
#include <string>


/* BoidFlock manages a group of Boid objects that 'perseive' each other. 
* It is tasked with iterating over the void objects and adjusting their velocityies (directions) beased on the mositioning and velosities of their peer. 
* 
* Multiple BoidFlocks can exist in a scene but a Boid from one flock will not 'perceive' boids from another flock. 
*/

class BoidFlock
{
public: // constructors

	BoidFlock(std::vector<Boid*> boids);
	BoidFlock(int num_of_boids, std::string sprite_sheet_file_path, float start_x_pos = 0, float start_y_pos = 0);
	~BoidFlock();

	// "rule of threes"
	BoidFlock(const BoidFlock&) = delete;
	BoidFlock& operator=(const BoidFlock&) = delete;

public: // logic

	void updateBoidLogic(float delta_time);
	void draw();

private: // logic

	void applySeparationLogic(Boid* boid, float& new_x_vel, float& new_y_vel);
	void applyAlignmentLogic(Boid* boid, float& new_x_vel, float& new_y_vel);
	void applyCohesionLogic(Boid* boid, float& new_x_vel, float& new_y_vel);
	void applyBorderAvoidanceLogic(Boid* boid, float& new_x_vel, float& new_y_vel);

private: // data
	std::vector<Boid*> boids;

	float protected_distance = 50;
	float visible_distance = 200;

	float avoid_weight = 0.05f;
	float alignment_weight = 0.1f;
	float cohesion_weight = 0.001f;
	// buffer space :(

	float margin_size = 100;
	float turn_factor = 0.1f;
};

