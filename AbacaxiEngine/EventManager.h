#pragma once

/*
	EventManager.h
	Purpose: Manage CommandInput type callbacks through sfml events. 
	A CommandInput type must be bound with the necessery arguments. 
	Then if a correspondent SFML event occurs, it will execute whatever
	function was bound to that command.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "pch.h"
#include "CommandKey.h"



namespace abx {



	/*
		@brief Manage CommandInput type callbacks through sfml events.
	*/
	class EventManager {



		std::vector<Ref<CommandKey>> m_keys;		//Container of commands. CommandKey holds a command input object


	public:



		/*
			@brief Constructor
		*/
		EventManager(SharedData* l_sharedData);



		/*
			@brief Compares sfml events to CommandInput objects in container.
			If the type, like sf::Keyboard or sf::Mouse, corresponds to 
			CommandInput's key, a callback will be called.
		*/
		void HandleEvent(sf::Event* l_event);



		/*
			@brief Check for realtime user inputs with no sfml events.
			If the type, like sf::Keyboard or sf::Mouse, corresponds to
			CommandInput's key, and CommandInput's isHold is true,
			a callback will be called.
		*/
		void HandleInput();



		/*
			@brief Removes all commands. Useful switching or destroying 
			machine states.
		*/
		void RemoveAll();



		/*
			@brief Binds a command input type to a container that will be called as an callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an entity will be passed within the command input type along with a keybaord code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param std::weak_ptr<Entity> entity
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template<class C>
		WeakRef<CommandInput> Bind(WeakRef<class Entity> l_entity, sf::Keyboard::Key l_keyCode, const bool& l_isHold);



		/*
			@brief Binds a command input type to a container that will be called as an callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an entity will be passed within the command input type along with a mouse code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param std::weak_ptr<Entity> entity
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template<class C>
		WeakRef<CommandInput> Bind(WeakRef<class Entity> l_entity, sf::Mouse::Button l_mouseButton, const bool& l_isHold);



		/*
			@brief Binds a command input type to a container that will be called as an callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, a shared data pointer will be passed within the command input type along with a keyboard code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param SharedData* sharedData
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template <class C>
		WeakRef<CommandInput> Bind(SharedData* l_sharedData, sf::Keyboard::Key l_keyCode, const bool& l_isHold);



		/*
			@brief Binds a command input type to a container that will be called as an callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, a shared data pointer will be passed within the command input type along with a mouse code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param SharedData* sharedData
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template <class C>
		WeakRef<CommandInput> Bind(SharedData* l_sharedData, sf::Mouse::Button l_mouseButton , const bool& l_isHold);
	};



	/*
		@brief Definition. Binds a command input type to a container that will be called as an callback
		whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
		In this case, an entity will be passed within the command input type along with a keybaord code.
		IsHold determines if callback will be called upon SFML events (false) or every frame(true).
		@param std::weak_ptr<Entity> entity
		@param sf::KeyBoard::Key keyCode
		const bool& isHold
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(WeakRef<class Entity> l_entity, sf::Keyboard::Key l_keyCode, const bool& l_isHold){
		
		for(auto& itr : m_keys)
			if (itr->GetKeyCode() == l_keyCode &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->BindEntity(l_entity);					//Binding entity
		newKey->SetKeyCode(l_keyCode);										//Binding key code to command input
		newKey->SetHold(l_isHold);
		m_keys.push_back(std::move(newKey));								//Transfering ownership to container
		return m_keys.back()->GetCommand();
	}
	
	
	
	/*
		@brief Definition. Binds a command input type to a container that will be called as an callback
		whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
		In this case, an entity will be passed within the command input type along with a mouse code.
		IsHold determines if callback will be called upon SFML events (false) or every frame(true).
		@param std::weak_ptr<Entity> entity
		@param sf::Mouse::Button mouseButton
		const bool& isHold
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(WeakRef<class Entity> l_entity, sf::Mouse::Button l_mouseButton, const bool& l_isHold){
		for (auto& itr : m_keys)
			if (itr->GetMouseCode() == l_mouseButton &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->BindEntity(l_entity);					//Binding entity
		newKey->SetMouseCode(l_mouseButton);										//Binding key code to command input
		newKey->SetHold(l_isHold);
		m_keys.push_back(std::move(newKey));								//Transfering ownership to container
		return m_keys.back()->GetCommand();
	}




	/*
		@brief Binds a command input type to a container that will be called as an callback
		whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
		In this case, a shared data pointer will be passed within the command input type along with a keyboard code.
		IsHold determines if callback will be called upon SFML events (false) or every frame(true).
		@param SharedData* sharedData
		@param sf::KeyBoard::Key keyCode
		const bool& isHold
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(SharedData* l_sharedData, sf::Keyboard::Key l_keyCode, const bool& l_isHold){
		for (auto& itr : m_keys)
			if (itr->GetKeyCode() == l_keyCode &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->BindSharedData(l_sharedData);			//Binding entity
		newKey->SetKeyCode(l_keyCode);										//Binding key code to command input
		newKey->SetHold(l_isHold);
		m_keys.push_back(std::move(newKey));								//Transfering ownership to container
		return m_keys.back()->GetCommand();
	}




	/*
		@brief Binds a command input type to a container that will be called as an callback
		whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
		In this case, a shared data pointer will be passed within the command input type along with a mouse code.
		IsHold determines if callback will be called upon SFML events (false) or every frame(true).
		@param SharedData* sharedData
		@param sf::KeyBoard::Key keyCode
		const bool& isHold
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(SharedData* l_sharedData, sf::Mouse::Button l_mouseButton, const bool& l_isHold){
		for (auto& itr : m_keys)
			if (itr->GetMouseCode() == l_mouseButton &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->BindSharedData(l_sharedData);			//Binding entity
		newKey->SetMouseCode(l_mouseButton);								//Binding key code to command input
		newKey->SetHold(l_isHold);
		m_keys.push_back(std::move(newKey));								//Transfering ownership to container
		return m_keys.back()->GetCommand();
	}


}