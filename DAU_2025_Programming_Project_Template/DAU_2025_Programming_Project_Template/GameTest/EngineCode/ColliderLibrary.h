#pragma once
#include <vector>

class Collider2D;

/* COLLIDER LIBRARY
* All colliders in the scene are STORED here. 
* Used by Collider2D to check for collition with other active colliders in the scene.
* 
* singlton class. 
*/

class sColliderLibrary
{
public: // logic

	// "rule of threes"
	sColliderLibrary(const sColliderLibrary&) = delete;
	sColliderLibrary& operator=(const sColliderLibrary&) = delete;

	static void createInstance();
	static void destroyInstance();
	static sColliderLibrary* getInstance();

	void addCollider(Collider2D* collider) { collider_library.push_back(collider); }
	void removeCollider(Collider2D* collider);

	const std::vector<Collider2D*>& getLibrary() const { return collider_library; }

private: // constructor

	sColliderLibrary();
	~sColliderLibrary();

private: // memory

	static sColliderLibrary* collider_library_single_instance;
	
	std::vector<Collider2D*> collider_library; //32
	// padding :(
};