#pragma once
#include "EngineCode/Positionable.h"
#include "EngineCode/SceneMember.h"
#include <memory>

class RectangleCollider2D;

class WallTile: Positionable, public SceneMember
{
public: // contructor

	WallTile(float x_pos = 0, float y_pos = 0, float size = 13);
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

