#pragma once
#include "EngineCode/Positionable.h"
#include "EngineCode/SceneMember.h"
#include <memory>

class RectangleCollider2D;

class WallTile: Positionable, SceneMember
{
public: // contructor

	WallTile(float x_pos, float y_pos, float size = 100);
	~WallTile();

	// rule of "threes"
	WallTile(const WallTile&) = delete;
	WallTile& operator=(const WallTile&) = delete;

public: // virtual logic

	void sceneUpdateLogic(float delta_time) override;
	void sceneDraw() override;
	void sceneDrawGizmos() override;

private: // data

	std::unique_ptr<RectangleCollider2D> collider;
};

