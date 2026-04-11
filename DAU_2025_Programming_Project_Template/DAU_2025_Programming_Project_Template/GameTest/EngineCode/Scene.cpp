#include "stdafx.h"
#include "Scene.h"
#include "EngineCode/SceneMember.h"
#include <fstream>
#include <string>

Scene::Scene()
{
	// add all sceneMembers into member_library
}

Scene::Scene(std::string file_path)
{
	std::ifstream scene_file(file_path);

	std::string line;

	while (std::getline(scene_file, line)) {
		OutputDebugStringA(line.c_str());
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

