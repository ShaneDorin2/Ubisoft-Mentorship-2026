#include "stdafx.h"
#include "ColliderLibrary.h"

sColliderLibrary* sColliderLibrary::collider_library_single_instance = nullptr;

void sColliderLibrary::createInstance()
{
    softAssert(collider_library_single_instance == nullptr, "Tried to create new ColliderLibrary instance when an instance already exists.");
    if (collider_library_single_instance == nullptr) collider_library_single_instance = new sColliderLibrary();
}

void sColliderLibrary::destroyInstance()
{
    assert(collider_library_single_instance != nullptr);
    delete collider_library_single_instance;
}

sColliderLibrary* sColliderLibrary::getInstance()
{
    assert(collider_library_single_instance != nullptr);
    return collider_library_single_instance;
}

void sColliderLibrary::removeCollider(Collider2D* collider)
{
    auto it = std::find(collider_library.begin(), collider_library.end(), collider);
    assert(it != collider_library.end()); // cannot remove a collider that has not been added. 

    collider_library.erase(it);
}

sColliderLibrary::sColliderLibrary() {}

sColliderLibrary::~sColliderLibrary()
{
    assert(collider_library.empty() == true);
    collider_library.clear(); // this feels redundant since it will never run if collider_library is not already empty. 
}
