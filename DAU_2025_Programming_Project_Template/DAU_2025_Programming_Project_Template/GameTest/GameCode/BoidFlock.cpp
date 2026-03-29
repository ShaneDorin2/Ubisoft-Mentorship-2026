#include "stdafx.h"
#include "BoidFlock.h"
#include <cmath>
#include <iostream>
#include <format>
#include <random>

BoidFlock::BoidFlock(std::vector<Boid>&& boids) : boids(std::move(boids))
// TO DO have an optional constructor where it takes the num of boids in the flock and creates the interally. 
{
	assert(boids.size() > 0);
}

// Constructor that creates its own Boid objects using a 1 by 1 sprite sheet. 
BoidFlock::BoidFlock(int num_of_boids, std::string sprite_sheet_file_path, float start_x_pos, float start_y_pos)
{
	assert(num_of_boids > 0);

	// build file path
	std::string file_path = (".\\TestData\\" + sprite_sheet_file_path).c_str();
	const char* file_path_const_char = file_path.c_str();

	// init start velocities (randomly selected for each boid)
	float start_x_velocity;
	float start_y_velocity;

	// random number generator
	// TODO move this somwhere else where the code can easilly be re-used. 
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> randomNoneZeroFloat(0.1f, 1.0f);

	// populate the flock. 
	boids.reserve(num_of_boids); // THIS IS CALLING "Boid(const Boid&) = delete;", CAUSING A CRASH !
	for (int i =0; i < num_of_boids ; i++) {

		start_x_velocity = randomNoneZeroFloat(gen);
		start_y_velocity = randomNoneZeroFloat(gen);

		boids.emplace_back( // THIS IS CALLING "Boid(const Boid&) = delete;", CAUSING A CRASH !
			start_x_pos, start_y_pos,
			new CSimpleSprite(file_path_const_char, 1, 1), 
			start_x_velocity, start_y_velocity
		);
	}
}

BoidFlock::~BoidFlock()
{}

// Based off of "https://vanhunteradams.com/Pico/Animal_Movement/Boids-algorithm.html". 
void BoidFlock::updateBoidLogic(float delta_time)
{
	float new_x_vel;
	float new_y_vel;

	for (Boid& boid : boids) {

		new_x_vel = boid.getXVelocity();
		new_y_vel = boid.getYVelocity();

		applySeparationLogic(boid, new_x_vel, new_y_vel);
		applyAlignmentLogic(boid, new_x_vel, new_y_vel);
		applyCohesionLogic(boid, new_x_vel, new_y_vel);
		applyBorderAvoidanceLogic(boid, new_x_vel, new_y_vel);

		boid.updateVelocity(new_x_vel, new_y_vel);
	}

	for (Boid& boid : boids) {
		
		boid.updatePosition(delta_time);
	}
}

void BoidFlock::draw()
{
	for (Boid& boid : boids) {

		boid.draw();
	}
}

void BoidFlock::applySeparationLogic(Boid& boid, float& new_x_vel, float& new_y_vel)
{
	float close_dy = 0;
	float close_dx = 0;
	float other_boid_distance;

	for (Boid& other_boid : boids) {
		if (&boid == &other_boid) continue;

		other_boid_distance = std::hypotf(
			boid.getX() - other_boid.getX(),
			boid.getY() - other_boid.getY());

		if (protected_distance >= other_boid_distance) {

			close_dx += (boid.getX() - other_boid.getX()) * (1 - other_boid_distance / protected_distance);
			close_dy += (boid.getY() - other_boid.getY()) * (1 - other_boid_distance / protected_distance);
		}
	}

	new_x_vel += close_dx * avoid_weight;
	new_y_vel += close_dy * avoid_weight;

}

void BoidFlock::applyAlignmentLogic(Boid& boid, float& new_x_vel, float& new_y_vel)
{
	float x_vel_avg = 0;
	float y_vel_avg = 0;
	float num_of_boid_neibords = 0;
	float other_boid_distance;

	for (Boid& other_boid : boids) {
		if (&boid == &other_boid) continue;

		other_boid_distance = std::hypotf( // i calculate this TWO times per other_boid, per frame. Is there a way to only calculate it once ? 
			boid.getX() - other_boid.getX(),
			boid.getY() - other_boid.getY());

		if (visible_distance >= other_boid_distance) {

			// Alignment
			x_vel_avg += other_boid.getXVelocity();
			y_vel_avg += other_boid.getYVelocity();
			num_of_boid_neibords++;
		}
	}

	if (num_of_boid_neibords != 0) {

		x_vel_avg = x_vel_avg / num_of_boid_neibords;
		y_vel_avg = y_vel_avg / num_of_boid_neibords;
		new_x_vel += (x_vel_avg - new_x_vel) * alignment_weight;
		new_y_vel += (y_vel_avg - new_y_vel) * alignment_weight;
	}
}

void BoidFlock::applyCohesionLogic(Boid& boid, float& new_x_vel, float& new_y_vel)
{

	float x_pos_avg = 0;
	float y_pos_avg = 0;
	float num_of_boid_neibords = 0;

	for (Boid& other_boid : boids) {
		if (&boid == &other_boid) continue;

		float other_boid_distance = std::hypotf( // i calculate this TWO times per other_boid, per frame. Is there a way to only calculate it once ? 
			boid.getX() - other_boid.getX(),
			boid.getY() - other_boid.getY());

		if (visible_distance >= other_boid_distance) {

			num_of_boid_neibords++;

			x_pos_avg += other_boid.getX();
			y_pos_avg += other_boid.getY();
		}
	}

	if (num_of_boid_neibords != 0) {

		x_pos_avg = x_pos_avg / num_of_boid_neibords;
		y_pos_avg = y_pos_avg / num_of_boid_neibords;
		new_x_vel += (x_pos_avg - boid.getX()) * cohesion_weight;
		new_y_vel += (y_pos_avg - boid.getY()) * cohesion_weight;
	}
}

void BoidFlock::applyBorderAvoidanceLogic(Boid& boid, float& new_x_vel, float& new_y_vel)
{
	// TODO, replace the consept of margins and, instead, create Wall objects that the boids will avoid. 

	assert(margin_size < APP_VIRTUAL_WIDTH / 2 && margin_size < APP_VIRTUAL_HEIGHT / 2);

	float left_margin = 0 + margin_size;
	float right_margin = APP_VIRTUAL_WIDTH - margin_size;
	float top_margin = 0 + margin_size;
	float bottom_margin = APP_VIRTUAL_HEIGHT - margin_size;

	// Screen border avoidance
	if (boid.getX() < left_margin) new_x_vel = boid.getXVelocity() + turn_factor;
	if (boid.getX() > right_margin) new_x_vel = boid.getXVelocity() - turn_factor;
	if (boid.getY() > bottom_margin) new_y_vel = boid.getYVelocity() - turn_factor;
	if (boid.getY() < top_margin) new_y_vel = boid.getYVelocity() + turn_factor;
}
