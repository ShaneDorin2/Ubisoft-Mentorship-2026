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
Scene* testScene;

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	// My event manager code 
	sEventManager::createInstance(); // createInstance must be called ONCE in the function.  
	sColliderLibrary::createInstance(); // createInstance must be called ONCE in the function.  

	testScene = new Scene(".\\TestData\\SceneFile.txt");
	//testScene->addMember<WallTile>(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{

	InputManager::processUserInput();

	testScene->updateLogic(deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	testScene->draw();
	testScene->drawGizmos();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{

	delete testScene;

	sEventManager::destroyInstance();
	sColliderLibrary::destroyInstance();

}