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
	float protected_distance = 150;
	float visible_distance = 200;
	float avoid_weight = 0.001;
	float alignment_weight = 0.01;
	float cohesion_weight = 0.001;


	float close_dy;
	float close_dx;

	float x_vel_avg;
	float y_vel_avg;
	float num_of_boid_neibords;

	float x_pos_avg;
	float y_pos_avg;

	for (Boid* boid : boids) {

		float new_x_vel = boid->getXVelocity();
		float new_y_vel = boid->getYVelocity();

		// Separation
		close_dy = 0;
		close_dx = 0;

		// Alignment
		x_vel_avg = 0;
		y_vel_avg = 0;
		num_of_boid_neibords = 0;

		// Cohesion
		x_pos_avg = 0;
		y_pos_avg = 0;

		for (Boid* other_boid : boids) {
			if (boid == other_boid) continue;

			// Separation
			if (protected_distance >= std::hypotf(
				boid->getX() - other_boid->getX(), 
				boid->getY() - other_boid->getY())
				) {
				close_dx += boid->getX() - other_boid->getX();
				close_dy += boid->getY() - other_boid->getY();
			}
			else if (visible_distance >= std::hypotf(
				boid->getX() - other_boid->getX(),
				boid->getY() - other_boid->getY())
				) {

				// Alignment
				x_vel_avg += other_boid->getXVelocity();
				y_vel_avg += other_boid->getYVelocity();
				num_of_boid_neibords++;

				// Cohesion
				x_pos_avg += other_boid->getX();
				y_pos_avg += other_boid->getY();
			}
		}

		// separation
		new_x_vel += close_dx * avoid_weight;
		new_y_vel += close_dy * avoid_weight;
		
		if (num_of_boid_neibords != 0) {

			// alignment
			x_vel_avg = x_vel_avg / num_of_boid_neibords;
			y_vel_avg = y_vel_avg / num_of_boid_neibords;
			new_x_vel += (x_vel_avg - new_x_vel) * alignment_weight;
			new_y_vel += (y_vel_avg - new_y_vel) * alignment_weight;

			// Cohesion
			x_pos_avg = x_pos_avg / num_of_boid_neibords;
			y_pos_avg = y_pos_avg / num_of_boid_neibords;
			new_x_vel += (x_pos_avg - boid->getX()) * cohesion_weight;
			new_y_vel += (y_pos_avg - boid->getY()) * cohesion_weight;
		}

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
