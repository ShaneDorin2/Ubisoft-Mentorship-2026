#pragma once
#include "Collider2D.h"
#include "CircleCollider2D.h"
#include "RectangleCollider2D.h"
#include <algorithm>
#include <Assert.h>
#include "ColliderLibrary.h"

/* Collition detection is what is called when wanting to detect a collition.
* Ideally, this is the only script that will half to be modified if a new type of collider is added to the engin. 
* TODO: find a better system to determin what type to use in the static_cast. Currently using a 2D switch case and it feels very very wrong. 
*/
namespace CollisionDetection
{	
	bool compareColliders(CircleCollider2D* collider_1, CircleCollider2D* collider_2) {

		return (
			// combined radus' squared
			pow(collider_1->getRadius() + collider_2->getRadius(), 2) >

			//squared distance
			pow(collider_1->getX() - collider_2->getX(), 2) +
			pow(collider_1->getY() - collider_2->getY(), 2)
			);
	}

	bool compareColliders(RectangleCollider2D* collider_1, RectangleCollider2D* collider_2) {

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

	bool compareColliders(CircleCollider2D* collider_1, RectangleCollider2D* collider_2) {
		
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
	bool compareColliders(RectangleCollider2D* collider_1, CircleCollider2D* collider_2) { return compareColliders(collider_2, collider_1); }

	std::vector<Collider2D*> getAllCollitions(Collider2D& collider)
	{
		std::vector<Collider2D*> return_vector;

		softAssert(collider.getActive(), "getAllCollitions() called on non-active collider.");

		// return empty vector is is_active == false. 
		if (collider.getActive() == false) {
			return return_vector;
		}

		for (Collider2D* other_collider : sColliderLibrary::getInstance()->getLibrary()) {
			if (&collider == other_collider) continue;

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

			default: break;
			}
		}
		return return_vector;
	}
}