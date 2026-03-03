#pragma once
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

/* EVENT MANAGER
* All Events in the game are DECLARED, STORED and TRIGGERED here. 
*
* sEventManager is a Singleton. Only one EventManager exists in the game.
* Implemented "Naive Singlton" (not thread-safe) using this example : https://refactoring.guru/design-patterns/singleton/cpp/example#example-0
* 
* // Singlton classes are named with an "s" at the begining. 
* 
*/
class sEventManager 
{
public: // definitions
	using ActionFunctionType = std::function<void()>; // a function type that has no parrameter and returns void. 

	enum eEvent // all events existing in the project are named in this Enume. 
		// TODO: move eEvent to its own file. 
	{
		// input events
		UP_INPUT,
		DOWN_INPUT,
		RIGHT_INPUT,
		LEFT_INPUT
	};

public: // logic

	// "rule of threes"
	sEventManager(const sEventManager&) = delete;
	sEventManager& operator=(const sEventManager&) = delete;

	static void createInstance(); 
	static void destroyInstance(); 
	static sEventManager* getInstance(); // offeres access to the singlton instance

	void subscribeTo(eEvent event_id, ActionFunctionType* subsctiber);
	void unSubscribeFrom(eEvent event_id, ActionFunctionType* subsctiber);
	void trigger(eEvent event_id);
	// note that there is no "createNewEvent()" fucntion. For the sake of organisation, all events will be created in this class (via the eEvent enum)

private: // constructors and destructors 
	
	sEventManager();
	~sEventManager();

private: // memory

	static sEventManager* event_manager_single_instance; // stores the singlton pointer

	std::unordered_map < eEvent, std::vector<ActionFunctionType*> > event_library;
	// turns out I can't compare ActionFunctionTypes but I CAN compare their POINTERS !

};

