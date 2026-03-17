//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------
#include <iostream>
#include "Player.h"
#include "EventManager.h"
#include "InputManager.h"
#include "BoidFlock.h"
#include "ColliderLibrary.h"

//------------------------------------------------------------------------
// My data
CSimpleSprite* placeHolderImage;
sEventManager* event_manager; // singleton
Player* player;
BoidFlock* boid_flock;

Collider2D* test_collider;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// My sprite code
	placeHolderImage = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderImage->SetScale(1.0f);

	// My event manager code 
	sEventManager::createInstance(); // createInstance must be called ONCE in the function.  
	sColliderLibrary::createInstance(); // createInstance must be called ONCE in the function.  

	// My player code
	player = new Player(400.0f, 400.0f, placeHolderImage);

	//TO DO: innit all scene elements here. 

	boid_flock = new BoidFlock(20, "PlaceHolderImage.png", APP_VIRTUAL_WIDTH/2, APP_VIRTUAL_HEIGHT / 2);
	test_collider = new Collider2D(CIRCLE, 100, true, nullptr, 100, 100); // TO DO : Create a 2nd constructor where I don't have to set parent to nullptr. 
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	InputManager::processUserInput();

	// apply input data
	player->updateLogic();

	// update player position
	player->updatePosition(deltaTime);

	boid_flock->updateBoidLogic(deltaTime);

	/* 
	Should I combine these two "player->" functions into one player->tick(deltaTime) function, 
	or is it best to keep UPDATE LOGIC and UPDATE POSITION seperate ?
	*/
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{

	player->draw();

	boid_flock->draw();

	for (Collider2D* collider : sColliderLibrary::getInstance()->getLibrary()) {
		collider->drawGizmo();
	}
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

	delete player; // player MUST be destroyed befor eventManager to satisfy assert(). 
	delete boid_flock;
	sEventManager::destroyInstance();
	sColliderLibrary::destroyInstance();

}