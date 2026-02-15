#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

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
protected: 

	// constructors and destructors 
	sEventManager();
	~sEventManager();

	static sEventManager* event_manager_single_instance; // stores the singlton pointer


public:

	// "rule of threes"
	sEventManager(const sEventManager&) = delete;
	sEventManager& operator=(const sEventManager&) = delete;

	static sEventManager* GetInstance(); // offeres access to the singlton

	// ----------------------------------------------------------------------------------------------------------------------------------

	using ActionFunctionType = std::function<void()>; // a function type that has no parrameter and returns void. 

	enum eEvent // all events existing in the project are named in this Enume. 
	{
		// input events
		UP_INPUT, 
		DOWN_INPUT,
		RIGHT_INPUT, 
		LEFT_INPUT
	};

	// ----------------------------------------------------------------------------------------------------------------------------------
	// public functions

	void subscribeTo(eEvent event_id, ActionFunctionType subsctiber);
	void unSubscribeFrom(eEvent event_id, ActionFunctionType subsctiber);
	void trigger(eEvent event_id);
	// note that there is no "createNewEvent()" fucntion. For the sake of organisation, all events will be created in this class (via the eEvent enum)

private:

	std::unordered_map < eEvent, std::vector<ActionFunctionType> > event_library;

};

