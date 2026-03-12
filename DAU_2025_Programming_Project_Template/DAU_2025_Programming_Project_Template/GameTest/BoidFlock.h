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

private: // data
	std::vector<Boid*> boids;
};

