#pragma once
#include "Collider2D.h"
#include "CircleCollider2D.h"
#include "RectangleCollider2D.h"
#include "RayCastCollider2D.h"
#include <algorithm>
#include <Assert.h>
#include "ColliderLibrary.h"

// windows have a macro for 'min' and 'max' that break std::min and std::max. This undefines these macros. 
#undef min
#undef max

/* Collition detection is what is called when wanting to detect a collition.
* Ideally, this is the only script that will half to be modified if a new type of collider is added to the engin. 
* TODO: find a better system to determin what type to use in the static_cast. Currently using a 2D switch case and it feels very very wrong. 
*/
namespace CollisionDetection
{	
	inline bool compareColliders(CircleCollider2D* collider_1, CircleCollider2D* collider_2) {

		return (
			// combined radus' squared
			pow(collider_1->getRadius() + collider_2->getRadius(), 2) >

			//squared distance
			pow(collider_1->getX() - collider_2->getX(), 2) +
			pow(collider_1->getY() - collider_2->getY(), 2)
			);
	}

	inline bool compareColliders(RectangleCollider2D* collider_1, RectangleCollider2D* collider_2) {

		return (
			abs(collider_1->getX() - collider_2->getX())		// x distance
			< 
			(collider_1->getWidth() + collider_2->getWidth())/2 // combined width /2
			&&
			abs(collider_1->getY() - collider_2->getY())		// y distance
			<
			(collider_1->getHight() + collider_2->getHight())/2	// combined hight /2
			);
	}

	inline bool compareColliders(CircleCollider2D* collider_1, RectangleCollider2D* collider_2) {
		
		// find closes point on square. 
		float closestX = std::clamp(
			collider_1->getX(), 
			collider_2->getX() - collider_2->getWidth() / 2, 
			collider_2->getX() + collider_2->getWidth() / 2);
		float closestY = std::clamp(
			collider_1->getY(), 
			collider_2->getY() - collider_2->getHight() / 2, 
			collider_2->getY() + collider_2->getHight() / 2);

		return (
			// distance_sq
			powf(closestX - collider_1->getX(), 2) + 
			powf(closestY - collider_1->getY(), 2)
			< 
			// radius_sq
			pow(collider_1->getRadius(), 2)
			);
	}
	inline bool compareColliders(RectangleCollider2D* collider_1, CircleCollider2D* collider_2) { return compareColliders(collider_2, collider_1); }

	// source : https://www.geeksforgeeks.org/dsa/check-line-touches-intersects-circle/
	inline bool compareColliders(RayCastCollider2D* collider_1, CircleCollider2D* collider_2) {
		float ray_start_x = collider_1->getX();
		float ray_start_y = collider_1->getY();
		float ray_end_x = ray_start_x + collider_1->getDirectionX() * collider_1->getLength();
		float ray_end_y = ray_start_y + collider_1->getDirectionY() * collider_1->getLength();


		//float a_closes_raycast_x = std::clamp(collider_2->getX(), ray_start_x, ray_end_x);
		//float a_closes_raycast_y = ray_start_y + collider_1->getDirectionY() * (a_closes_raycast_x / ray_end_x);

		//float b_closes_raycast_y = std::clamp(collider_2->getY(), ray_start_y, ray_end_y);
		//float b_closes_raycast_x = ray_start_x + collider_1->getDirectionX() * (a_closes_raycast_y / ray_end_y);

		// distance of ray
		float dx = ray_end_x - ray_start_x;
		float dy = ray_end_y - ray_start_y;

		// distant from ray start to circle center. 
		float start_center_dx = collider_2->getX() - ray_start_x;
		float start_center_dy = collider_2->getY() - ray_start_y;

		float ray_length_sq = collider_1->getLength();

		float closest_part_of_ray = (start_center_dx * dx + start_center_dy * dy) / ray_length_sq;

		// clamp
		closest_part_of_ray = std::clamp(closest_part_of_ray, 0.f, 1.f);

		// get coordinates of closest part of ray
		float closest_x = ray_start_x + closest_part_of_ray * dx;
		float closest_y = ray_start_y + closest_part_of_ray * dy;

		// get distance sq
		float distance_sq = powf(closest_x - collider_1->getX(), 2) + powf(closest_y - collider_1->getY(), 2);

		return (powf(collider_2->getRadius(), 2) > distance_sq);




		//// line information. 
		//float a = collider_1->getDirectionX();
		//float b = collider_1->getDirectionY();
		//float c = -(a * collider_1->getX()) - (b * collider_1->getY());

		//// circle center position
		//float x = collider_2->getX();
		//float y = collider_2->getY();

		//// find distance between circle center and nearest point on raycast. 
		//float distance = (abs(a * x + b * y + c)) / sqrt(a * a + b * b);

		//return (collider_2->getRadius() >= distance);
	} 
	inline bool compareColliders(CircleCollider2D* collider_1, RayCastCollider2D* collider_2) { return compareColliders(collider_2, collider_1); }

	// "slab method"
	// source: https://www.youtube.com/shorts/GqwUHXvQ7oA
	inline bool compareColliders(RayCastCollider2D* collider_1, RectangleCollider2D* collider_2) {
		float ray_start_x = collider_1->getX();
		float ray_start_y = collider_1->getY();
		float ray_end_x = ray_start_x + collider_1->getDirectionX() * collider_1->getLength();
		float ray_end_y = ray_start_y + collider_1->getDirectionY() * collider_1->getLength();

		// distance of ray
		float dx = ray_end_x - ray_start_x;
		float dy = ray_end_y - ray_start_y;


		// rectangle bounds
		float left = collider_2->getX() - collider_2->getWidth() * 0.5f;
		float right = collider_2->getX() + collider_2->getWidth() * 0.5f;
		float top = collider_2->getY() - collider_2->getHight() * 0.5f;
		float bottom = collider_2->getY() + collider_2->getHight() * 0.5f;

		float tMin = 0.f;
		float tMax = 1.f;

		// x slab
		if (dx != 0.f) {
			float tx1 = (left - ray_start_x) / dx;
			float tx2 = (right - ray_start_x) / dx;

			float txMin = std::min(6.f, 5.f);
			float txMax = std::max(tx1, tx2);

			tMin = std::max(tMin, txMin);
			tMax = std::min(tMax, txMax);
		}
		else
		{
			// ray is vertical
			if (ray_start_x < left || ray_start_x > right) return false;
		}

		// y slab
		if (dy != 0.f) {
			float ty1 = (top - ray_start_y) / dy;
			float ty2 = (bottom - ray_start_y) / dy;

			float tyMin = std::min(ty1, ty2);
			float tyMax = std::max(ty1, ty2);

			tMin = std::max(tMin, tyMin);
			tMax = std::min(tMax, tyMax);
		}
		else
		{
			// ray is horizontal
			if (ray_start_y < top || ray_start_y > bottom) return false;
		}

		return tMax >= tMin;
	}
	inline bool compareColliders(RectangleCollider2D* collider_1, RayCastCollider2D* collider_2) { return compareColliders(collider_2, collider_1); }



	inline std::vector<Collider2D*> getAllCollitions(Collider2D& collider, bool of_type_trigger)
	{
		std::vector<Collider2D*> return_vector;

		softAssert(collider.getActive(), "getAllCollitions() called on non-active collider.");

		// return empty vector is is_active == false. 
		if (collider.getActive() == false) {
			return return_vector;
		}

		for (Collider2D* other_collider : sColliderLibrary::getInstance()->getLibrary()) {
			if (&collider == other_collider) continue;
			if (other_collider->getTrigger() != of_type_trigger) continue;

			// I am embarrassed by this 2D switch case but I can't think of any better way to do this. 
			switch (collider.getShape())
			{
			case CIRCLE:

				switch (other_collider->getShape())
				{
				case CIRCLE:
					if (compareColliders(static_cast<CircleCollider2D*>(&collider), static_cast<CircleCollider2D*>(other_collider)))
						return_vector.push_back(other_collider);
					break;

				case RECTANGLE:
					if (compareColliders(static_cast<CircleCollider2D*>(&collider), static_cast<RectangleCollider2D*>(other_collider)))
						return_vector.push_back(other_collider);
					break;

				default: break;
				}
				break;

			case RECTANGLE:
				switch (other_collider->getShape())
				{
				case CIRCLE:
					if (compareColliders(static_cast<RectangleCollider2D*>(&collider), static_cast<CircleCollider2D*>(other_collider)))
						return_vector.push_back(other_collider);
					break;

				case RECTANGLE:
					if (compareColliders(static_cast<RectangleCollider2D*>(&collider), static_cast<RectangleCollider2D*>(other_collider)))
						return_vector.push_back(other_collider);
					break;

				default: break;
				}
				break;

			//case RAYCAST:
			//	switch (other_collider->getShape())
			//	{
			//	case CIRCLE:
			//		if (compareColliders(static_cast<RectangleCollider2D*>(&collider), static_cast<CircleCollider2D*>(other_collider)))
			//			return_vector.push_back(other_collider);
			//		break;

			//	case RECTANGLE:
			//		if (compareColliders(static_cast<RectangleCollider2D*>(&collider), static_cast<RectangleCollider2D*>(other_collider)))
			//			return_vector.push_back(other_collider);
			//		break;

			//	default: break;
			//	}
			//	break;

			default: break;
			}
		}
		return return_vector;
	}
}