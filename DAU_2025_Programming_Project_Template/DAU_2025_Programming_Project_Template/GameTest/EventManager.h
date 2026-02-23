#pragma once
#include <functional>
#include <unordered_map>
#include "Events.h"

/* EVENT MANAGER
* All Events in this game are DECLARED, STORED and TRIGGERED here. 
*
* Only one EventManager exists in the game. (Does that mean it's called a singlton ?)
* Implemented "Naive Singlton" (not thread-safe) using this example : https://refactoring.guru/design-patterns/singleton/cpp/example#example-0
* 
* // Singlton classes are named with an "s" at the begining. 
* 
*/

class sEventManager 
{

public:

	using ActionFunctionType = std::function<void()>; // a function type that has no parrameter and returns void.

public:

	static sEventManager* getInstance(); // offeres access to the singlton
	static void createInstance(); // offeres access to the singlton
	static void destroyInstance(); // offeres access to the singlton

	// ----------------------------------------------------------------------------------------------------------------------------------
	// public functions

	void subscribeTo(eEvent event_id, ActionFunctionType* subsctiber);
	void unSubscribeFrom(eEvent event_id, ActionFunctionType* subsctiber);
	void trigger(eEvent event_id);
	// note that there is no "createNewEvent()" fucntion. For the sake of organisation, all events will be created in this class (via the eEvent enum)

private:
	// constructors and destructors 
	sEventManager();
	~sEventManager();
	sEventManager(const sEventManager&) = delete;
	sEventManager& operator=(const sEventManager&) = delete;

	static sEventManager* event_manager_single_instance; // stores the singlton pointer

private:
	std::unordered_map < eEvent, std::vector<ActionFunctionType*> > event_library;
	// turns out I can't compare ActionFunctionTypes but I CAN compare their POINTERS !

};

