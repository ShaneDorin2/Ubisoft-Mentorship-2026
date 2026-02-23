#include "stdafx.h"
#include "EventManager.h"

sEventManager* sEventManager::event_manager_single_instance = nullptr;

sEventManager::sEventManager()
{
}

sEventManager::~sEventManager()
{
	// Do i have anything to deleit here ? 
	assert(event_library.empty());
	event_library.clear();
}

void sEventManager::createInstance()
{
	assert(event_manager_single_instance == nullptr);
	event_manager_single_instance = new sEventManager();
}

void sEventManager::destroyInstance()
{
	assert(event_manager_single_instance != nullptr);
	delete event_manager_single_instance;
}

sEventManager* sEventManager::getInstance()
{
	assert(event_manager_single_instance != nullptr);
	return event_manager_single_instance;
}

void sEventManager::subscribeTo(eEvent event_id, ActionFunctionType* subscriber)
{
	// if Event ID is not already present in the event_library, add it. 
	if (event_library.count(event_id) == 0) {
		event_library.insert(std::pair<eEvent, std::vector<ActionFunctionType*>>(event_id, std::vector<ActionFunctionType*>()));
	}

	event_library[event_id].push_back(subscriber);
}

void sEventManager::unSubscribeFrom(eEvent event_id, ActionFunctionType* subscriber)
{
	// remove subscribed function from event's vector. 
	auto it = std::find(event_library[event_id].begin(), event_library[event_id].end(), subscriber);
	if (it != event_library[event_id].end())
	{
		event_library[event_id].erase(it);
	}

	// if event's vector is not empty, remove event from library. 
	if (event_library[event_id].size() == 0) {
		event_library.erase(event_id);
	}
}

void sEventManager::trigger(eEvent event_id)
{
	if (event_library.count(event_id) == 0) {
		// this event has no subscribers. 
		// TODO, add a debug message here. 
		return;
	}

	for (ActionFunctionType* subscriber : event_library[event_id]) {
		(*subscriber)();
	}
}
 

