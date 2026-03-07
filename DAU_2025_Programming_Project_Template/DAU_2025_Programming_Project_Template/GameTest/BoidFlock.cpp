#include "stdafx.h"
#include "BoidFlock.h"
#include <cmath>

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
	// TODO put this data somewhere else
	float protectedDistance = 100;
	float visibleDistance = 50;
	float avoidWeight = 1;


	float close_dy = 0;
	float close_dx = 0;

	for (Boid* boid : boids) {

		// Separation

		close_dy = 0;
		close_dx = 0;

		for (Boid* other_boid : boids) {
			if (boid == other_boid) continue;

			if (protectedDistance >= std::hypotf(
				boid->getX() - other_boid->getX(), 
				boid->getY() - other_boid->getY())
				) {
				close_dx += boid->getX() - other_boid->getX();
				close_dy += boid->getY() - other_boid->getY();
			}
		}

		float new_x_vel = boid->getXVelocity() + close_dx * avoidWeight;
		float new_y_vel = boid->getYVelocity() + close_dy * avoidWeight;
		boid->updateVelocity(new_x_vel, new_y_vel);
		
	}

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
