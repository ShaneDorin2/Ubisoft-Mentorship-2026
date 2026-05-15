#pragma once
#include <memory>
#include <EngineCode/Positionable.h>
#include <EngineCode/CircleCollider2D.h>

class AngelDetectionZone
{
public: // contrsuctor

	AngelDetectionZone(Positionable* parent, float radius);
	~AngelDetectionZone();

	// "rule of threes"
	AngelDetectionZone(const AngelDetectionZone&) = delete;
	AngelDetectionZone& operator=(const AngelDetectionZone&) = delete;

public: // logic

	void checkForNumOfAngelsInZone();
	void drawGizmo(float r, float g, float b);
	const int& getNumOfAngelsInZone() { return num_of_angels_in_zone; }

private: // data

	std::unique_ptr<CircleCollider2D> collider;
	int num_of_angels_in_zone;

};

