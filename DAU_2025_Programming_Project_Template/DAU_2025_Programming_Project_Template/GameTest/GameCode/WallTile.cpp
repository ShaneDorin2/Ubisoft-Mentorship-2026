#include "stdafx.h"
#include "WallTile.h"
#include "EngineCode/RectangleCollider2D.h"

WallTile::WallTile(float x_pos, float y_pos, float size) :
    Positionable(x_pos, y_pos),
    collider(new RectangleCollider2D(size, size, false, this))
{}

WallTile::~WallTile()
{}

void WallTile::sceneUpdateLogic(float delta_time)
{}

void WallTile::sceneDraw()
{}

void WallTile::sceneDrawGizmos()
{
    collider->drawGizmo();
}
