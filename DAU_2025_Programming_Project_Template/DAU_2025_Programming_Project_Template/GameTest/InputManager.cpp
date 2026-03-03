#include "stdafx.h"
#include "InputManager.h"

#include "App/app.h"
#include "EventManager.h"

void InputManager::processUserInput()
{
	sEventManager* event_manager = sEventManager::getInstance();


	// Directional inputs (WASD)

	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		event_manager->trigger(eEvent::RIGHT_INPUT);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		event_manager->trigger(eEvent::LEFT_INPUT);
	}
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		event_manager->trigger(eEvent::UP_INPUT);
	}
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		event_manager->trigger(eEvent::DOWN_INPUT);
	}
}
