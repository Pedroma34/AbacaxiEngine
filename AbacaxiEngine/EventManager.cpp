



/*
	EventManager.cpp
	Purpose: Manage CommandInput type callbacks through sfml events.
	A CommandInput type must be bound with the necessery arguments.
	Then if a correspondent SFML event occurs, it will execute whatever
	function was bound to that command.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/




#include "pch.h"
#include "EventManager.h"




namespace abx {




	/*___________________________________________________________________*/
	EventManager::EventManager()  :
	m_keys()
	{
		SharedData::SetEventMgr(this);
	}
	/*___________________________________________________________________*/




	/*___________________________________________________________________*/
	void EventManager::HandleEvent(sf::Event* l_event){

		/*Events in container*/
		for (auto& itr : m_keys)						     //Executing commands that requires an event
			if (itr->GetEventType() == l_event->type) {

				if (itr->GetKeyCode() != sf::Keyboard::Unknown) {
					if (l_event->key.code == itr->GetKeyCode()) {
						itr->Execute(*l_event);
						break;
					}
				}

				else if (itr->GetMouseCode() != sf::Mouse::Button::ButtonCount) {
					if (l_event->mouseButton.button == itr->GetMouseCode()) {
						itr->Execute(*l_event);
						break;
					}
				}

				itr->Execute(*l_event);
			}
			
		

		/*Keyboard*/
		if (l_event->type == sf::Event::KeyPressed) {		 //Checking if this event was a keyboard event

			const auto& keyEventCode = l_event->key.code;

			for (auto& itr : m_keys)

				if (itr->GetKeyCode() == keyEventCode &&
					!itr->isHold())

					if (!itr->GetCommand().expired()) {		 //Checking if command is in memory

						itr->Execute();						 //Executing command
						break;

					}
				
		}

		/*Keyboard Release*/
		if (l_event->type == sf::Event::KeyReleased) {		 //Checking if this event was a keyboard releaseevent

			const auto& keyEventCode = l_event->key.code;

			for (auto& itr : m_keys)

				if (itr->GetKeyCode() == keyEventCode)

					if (!itr->GetCommand().expired()) {		 //Checking if command is in memory

						itr->Undo();						 //Undo command
						break;

					}

		}

		/*Mouse*/
		if (l_event->type == sf::Event::MouseButtonPressed) {		 //Checking if this event was a mouse event

			const auto& mouseButton = l_event->mouseButton.button;

			for (auto& itr : m_keys)

				if (itr->GetMouseCode() == mouseButton &&
					!itr->isHold())

					if (!itr->GetCommand().expired()) {				 //Checking if command is in memory

						itr->Execute();								 //Executing command
						break;

					}

		}

		/*Mouse Release*/
		if (l_event->type == sf::Event::MouseButtonReleased) {		 //Checking if this event was a mouse release event

			const auto& mouseButton = l_event->mouseButton.button;

			for (auto& itr : m_keys)

				if (itr->GetMouseCode() == mouseButton)

					if (!itr->GetCommand().expired()) {				 //Checking if command is in memory

						itr->Undo();								 //Undo command
						break;

					}

		}

	}
	/*___________________________________________________________________*/




	/*___________________________________________________________________*/
	void EventManager::HandleInput(){
		for (auto& itr : m_keys) {

			if (sf::Keyboard::isKeyPressed(
				itr->GetKeyCode()) && 
				itr->isHold()
				)
				itr->Execute();

			else if (sf::Mouse::isButtonPressed(
				itr->GetMouseCode()) && 
				itr->isHold()
				)
				itr->Execute();
		}
	}
	/*___________________________________________________________________*/




	/*___________________________________________________________________*/
	void EventManager::RemoveAll(){
		m_keys.clear();
	}
	/*___________________________________________________________________*/




	/*___________________________________________________________________*/
	unsigned int EventManager::GetSize(){
		return m_keys.size();
	}
	/*___________________________________________________________________*/




}