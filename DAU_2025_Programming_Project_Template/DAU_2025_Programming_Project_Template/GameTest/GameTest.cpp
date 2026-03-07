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

//------------------------------------------------------------------------
// My data
CSimpleSprite* placeHolderImage;
CSimpleSprite* placeHolderBoidImage1;
CSimpleSprite* placeHolderBoidImage2;
CSimpleSprite* placeHolderBoidImage3;
CSimpleSprite* placeHolderBoidImage4;
CSimpleSprite* placeHolderBoidImage5;
sEventManager* event_manager; // singleton
Player* player;
BoidFlock* boid_flock;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// My sprite code
	placeHolderImage = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderImage->SetScale(1.0f);

	placeHolderBoidImage1 = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderBoidImage1->SetScale(0.5f);
	placeHolderBoidImage2 = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderBoidImage2->SetScale(0.5f);
	placeHolderBoidImage3 = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderBoidImage3->SetScale(0.5f);
	placeHolderBoidImage4 = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderBoidImage4->SetScale(0.5f);
	placeHolderBoidImage5 = App::CreateSprite(".\\TestData\\PlaceHolderImage.png", 1, 1);
	placeHolderBoidImage5->SetScale(0.5f);

	// My event manager code 
	sEventManager::createInstance(); // createInstance must be called ONCE in the function.  

	// My player code
	player = new Player(400.0f, 400.0f, placeHolderImage);

	//TO DO: innit all scene elements here. 

	std::vector<Boid*> boid_list = { 
		new Boid(0, 0, placeHolderBoidImage1, -1, -1),
		new Boid(100, 0, placeHolderBoidImage2, -1, 1),
		new Boid(0, 100, placeHolderBoidImage3, 1, -1),
		new Boid(-100, 0, placeHolderBoidImage4),
		new Boid(0, -100, placeHolderBoidImage5)
	};
	boid_flock = new BoidFlock(std::move(boid_list));
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	InputManager::processUserInput();

	// apply input data
	player->updateVelocity();

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

}