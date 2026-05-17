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

// singltons to create instances
#include "EngineCode\EventManager.h" // to create instance here.
#include "EngineCode\ColliderLibrary.h" // to create instance here. 

#include "EngineCode\InputManager.h"

#include "EngineCode\Scene.h"
#include "GameCode\WallTile.h"

//------------------------------------------------------------------------
// My data
Scene* test_scene;
CSimpleSprite* background_image;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// My event manager code 
	sEventManager::createInstance(); // createInstance must be called ONCE in the function.  
	sColliderLibrary::createInstance(); // createInstance must be called ONCE in the function.  

	test_scene = new Scene(".\\TestData\\CourtYardScene.txt");

	//background_image = App::CreateSprite(".\\TestData\\mapGrid.png", 1, 1); // for debugging
	background_image = App::CreateSprite(".\\TestData\\map.png", 1, 1);
	background_image->SetPosition(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
	background_image->SetScale(0.4);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	InputManager::processUserInput();

	test_scene->updateLogic(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	background_image->Draw();
	test_scene->draw();
	test_scene->drawGizmos();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

	delete test_scene;
	delete background_image;

	sEventManager::destroyInstance();
	sColliderLibrary::destroyInstance();

}