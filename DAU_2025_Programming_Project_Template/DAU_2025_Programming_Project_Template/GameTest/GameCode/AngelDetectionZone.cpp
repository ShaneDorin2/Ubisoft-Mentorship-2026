#include "stdafx.h"
#include "AngelDetectionZone.h"
#include <EngineCode/CollisionDetection.h>
#include <string>

AngelDetectionZone::AngelDetectionZone(Positionable* parent, float radius) :
collider(new CircleCollider2D(radius, true, parent))
{}

AngelDetectionZone::~AngelDetectionZone()
{}

void AngelDetectionZone::checkForNumOfAngelsInZone()
{
	std::vector<Collider2D*> collisions = CollisionDetection::getAllCollitions(*collider, true);
	num_of_angels_in_zone = collisions.size();
	std::string num = std::to_string(num_of_angels_in_zone);
	debugOutput(num);
}

void AngelDetectionZone::drawGizmo(float r, float g, float b)
{
	collider->drawGizmo(r, g, b);
}
