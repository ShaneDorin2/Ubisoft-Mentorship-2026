#include "stdafx.h"
#include "Scene.h"
#include "EngineCode/SceneMember.h"
#include <fstream>
#include <string>
#include <assert.h>
#include <GameCode/WallTile.h>
#include <App/AppSettings.h>
#include <GameCode/Player.h>

Scene::Scene()
{
	// add all sceneMembers into member_library
}

Scene::Scene(std::string file_path)
{
	std::ifstream scene_file(file_path);
	std::string line;

	int row_position =0;
	int col_position;

	while (std::getline(scene_file, line)) {

		col_position = 0;
		
		for (char letter : line) {

			detectTypeAndAdd(letter, 32-row_position, col_position);
			col_position++;
		}
		row_position++;
	}
}

Scene::~Scene()
{
	// destroy all objects in sceneMember
}

void Scene::updateLogic(float delta_time)
{
	for (std::unique_ptr<SceneMember>& member : member_library) {
		if (!member->scene_is_active) continue;
		member->sceneUpdateLogic(delta_time);
	}
}

void Scene::draw()
{
	for (std::unique_ptr<SceneMember>& member : member_library) {
		if (!member->scene_is_active) continue;
		member->sceneDraw();
	}
}

void Scene::drawGizmos()
{
	for (std::unique_ptr<SceneMember>& member : member_library) {
		if (!member->scene_is_active) continue;
		member->sceneDrawGizmos();
	}
}

void Scene::detectTypeAndAdd(char character, int row, int col)
{
	switch (character)
	{
	case '.': //nothing
		break;
	case 'w':
		addMember<WallTile>(col*15 + 61, row* 15 + 120); // TO DO store these numbers somewhere (create the consept of scene size?)
		break;	 
	case 'p':
		addMember<Player>(col* 15 + 61, row* 15 + 120);
		break;
	default:
		softAssert(false, "An unknown character was found in the SceneFile.");
		break;
	}
}

