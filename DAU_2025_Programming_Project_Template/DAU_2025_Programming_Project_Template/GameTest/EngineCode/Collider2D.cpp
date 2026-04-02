#include "stdafx.h"
#include "Collider2D.h"
#include "ColliderLibrary.h"
#include <cmath>

void Collider2D::setActive(bool new_active_status)
{
    if (new_active_status == is_active) return;
    is_active = new_active_status;

    if (new_active_status == true) {
        sColliderLibrary::getInstance()->addCollider(this);
    }
    else
    {
        sColliderLibrary::getInstance()->removeCollider(this);
    }
}

std::vector<Collider2D*> Collider2D::getAllCollitions()
{
    std::vector<Collider2D*> return_vector;

    softAssert(is_active == true, "getAllCollitions() called on non-active collider.");

    if (is_active == false) {
        return return_vector;
    }

    for (Collider2D* other_collider : sColliderLibrary::getInstance()->getLibrary()) {
        if (other_collider == this) continue;

        if (isCollidingWith(other_collider)) return_vector.push_back(other_collider);
    }

    return return_vector;
}

Collider2D::Collider2D(eColliderShape shape, bool is_trigger, Positionable* parent, float x_pos, float y_pos) :
    is_trigger(is_trigger), parent(parent), x_pos(x_pos), y_pos(y_pos)
{
    assert(parent != nullptr || (x_pos != NULL && y_pos != NULL)); // a collider without a parent MUST be porvided an x,y position. 

    if (parent != nullptr) {
        has_parent = true;
    }
    else {
        has_parent = false;
    }

    sColliderLibrary::getInstance()->addCollider(this);
}

Collider2D::~Collider2D()
{
    if (is_active == true) sColliderLibrary::getInstance()->removeCollider(this);
}
