#include "stdafx.h"
#include "Scene.h"
#include "EngineCode/SceneMember.h"

Scene::Scene()
{
	// add all sceneMembers into member_library
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

void Scene::addMember(std::unique_ptr<SceneMember> new_member, float pos_x, float pos_y)
{
	member_library.push_back(std::move(new_member));
}
