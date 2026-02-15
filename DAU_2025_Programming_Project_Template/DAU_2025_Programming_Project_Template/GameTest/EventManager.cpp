#include "stdafx.h"
#include "EventManager.h"

sEventManager::sEventManager()
{
}

sEventManager::~sEventManager()
{
	// Do i have anything to deleit here ? 
}

sEventManager* sEventManager::GetInstance()
{
	if (event_manager_single_instance == nullptr) {
		event_manager_single_instance = new sEventManager();
	}
	return event_manager_single_instance;
}

void sEventManager::subscribeTo(eEvent event_id, ActionFunctionType subsctiber)
{
	// if Event ID is not already present in the event_library, add it. 
	if (event_library.count(event_id) == 0) {
		event_library.insert(std::pair<eEvent, std::vector<ActionFunctionType>>(event_id, std::vector<ActionFunctionType>()));
	}

	event_library[event_id].push_back(subsctiber);
}

void sEventManager::unSubscribeFrom(eEvent event_id, ActionFunctionType subsctiber)
{
	// remove subscribed function from event's vector. 
	auto it = std::find(event_library[event_id].begin(), event_library[event_id].end(), subsctiber);
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

	for (ActionFunctionType subscriber : event_library[event_id]) {
		subscriber();
	}
}
 

