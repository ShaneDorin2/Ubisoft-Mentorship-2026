#include "stdafx.h"
#include "BoidFlock.h"

BoidFlock::BoidFlock(std::vector<Boid*> boids) : boids(std::move(boids))
{}

BoidFlock::~BoidFlock()
{
	for (Boid* boid : boids) {
		delete boid;
	}
}

// going to base this off of "https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html". 
void BoidFlock::updateBoidLogic(float delta_time)
{
	for (Boid* boid : boids) {
 
		boid->updatePosition(delta_time);

	}
}

void BoidFlock::draw()
{
	for (Boid* boid : boids) {

		boid->draw();

	}
}
