#include "stdafx.h"
#include "Collider2D.h"

#include "ColliderLibrary.h"
#include <cmath>
#include "App/AppSettings.h" // for pi, for drawCircle
#include "App/app.h" // for DrawLine()

Collider2D::Collider2D(eColliderShape shape, float radius, bool is_trigger, Positionable* parent, float x_pos, float y_pos) :
    shape(shape), radius(radius), is_trigger(is_trigger), parent(parent), x_pos(x_pos), y_pos(y_pos)
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

std::vector<Collider2D*> Collider2D::getAllCollitions()
{
    std::vector<Collider2D*> return_vector;
    
    softAssert(is_active == true, "getAllCollitions() called on non-active collider.");

    if (is_active == false) {
        return return_vector;
    }
    

    for (Collider2D* other_collider : sColliderLibrary::getInstance()->getLibrary()) {
        if (other_collider == this) continue;

        switch (other_collider->getShape())
        {
        case CIRCLE:
            if (compare2CircleCollitions(other_collider)) {
                return_vector.push_back(other_collider);
            }
            break;

        case RECTANGLE:
            assert(false); // TO DO, implement square colliders. 
            break;

        default:
            assert(false); // All colliders must have a eColliderShape.
            break;
        }
    }

    return return_vector;
}

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

void Collider2D::drawGizmo()
{
    assert(shape == CIRCLE); // other shapes are not yet supported. 

    if (has_parent) 
    {
        drawCircle(parent->getXPos(), parent->getYPos(), radius, 10);
    }
    else 
    {
        drawCircle(x_pos, y_pos, radius, 15);
    }
}

void Collider2D::drawCircle(float x_center, float y_center, float radius, int num_of_sides)
{
    assert(num_of_sides > 0);

    float angleStep = 2.0f * PI / num_of_sides;

    for (int i = 0; i < num_of_sides; i++)
    {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        float x1 = x_center + cosf(angle1) * radius;
        float y1 = y_center + sinf(angle1) * radius;

        float x2 = x_center + cosf(angle2) * radius;
        float y2 = y_center + sinf(angle2) * radius;

        App::DrawLine(x1, y1, x2, y2, 1, 0, 0); // white by default. 
    }
    App::DrawLine(x_center, y_center, x_center + radius, y_center, 1, 0, 0);
}

bool Collider2D::compare2CircleCollitions(Collider2D* other_collider)
{    
    float x_a, y_a, x_b, y_b;

    if (has_parent) 
    {
        x_a = parent->getXPos();
        y_a = parent->getYPos();
    }
    else 
    {
        x_a = x_pos;
        y_a = y_pos;
    }

    if (other_collider->has_parent) 
    {
        x_b = other_collider->parent->getXPos();
        y_b = other_collider->parent->getYPos();
    }
    else 
    {
        x_b = other_collider->getX();
        y_b = other_collider->getY();
    }

    return std::hypotf(
        x_a - x_b,
        y_a - x_b)
        <
        (radius + other_collider->getRadius());
}
