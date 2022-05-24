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
		@brief Manage CommandInput type callbacks using sfml events.
		It's able do bound command input types to a container that will
		be processed while SFML events are pulled. If an event matches
		with the event in the container, it will execute whatever command
		was bound to it.
		Example: 
		Bind<CommandJump>(player, sf::Keyboard::Space, false) //CommandJump is a derived class from Command Input
		This method will attach an entity to the command. If the space bar is pressed,
		the EventManager will call the Execute function inside the Command Key which 
		will also call the Execute function from a Command Input, which will carry the logic
		of making the entity jump.
		In order to create a callback, it is necessary to create a Command Input derived class,
		for instance CommandJump : public Command Input, and create an execute function
		that either takes no parameter, an entity, or an event type.
		See Command Input derived classes to have an idea.
	*/
	class EventManager {



		std::vector<Ref<CommandKey>> m_keys;		//Container of commands. CommandKey holds a command input object


	public:



		/*
			@brief Constructor
		*/
		EventManager();



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
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an entity will be passed within the command input type along with a keybaord code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param std::weak_ptr<Entity> entity
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template<class C>
		WeakRef<CommandInput> Bind(WeakRef<class Entity> l_entity,
			sf::Keyboard::Key l_keyCode, 
			const bool& l_isHold
		);



		/*
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an entity will be passed within the command input type along with a mouse code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param std::weak_ptr<Entity> entity
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template<class C>
		WeakRef<CommandInput> Bind(
			WeakRef<class Entity> l_entity, 
			sf::Mouse::Button l_mouseButton, 
			const bool& l_isHold
		);



		/*
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, a shared data pointer will be passed within the command input type along with a keyboard code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param SharedData* sharedData
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template <class C>
		WeakRef<CommandInput> Bind(
			sf::Keyboard::Key l_keyCode, 
			const bool& l_isHold
		);



		/*
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, a shared data pointer will be passed within the command input type along with a mouse code.
			IsHold determines if callback will be called upon SFML events (false) or every frame(true).
			@param SharedData* sharedData
			@param sf::KeyBoard::Key keyCode
			const bool& isHold
		*/
		template <class C>
		WeakRef<CommandInput> Bind(
			sf::Mouse::Button l_mouseButton, 
			const bool& l_isHold
		);



		/*
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an entity pointer with an event type will be passed.
			The execute command will be called when the current sfml event matches with the event passed as a parameter.
			This method is useful when there's something to be done with said entity if said event is happening.
			@param std::weak_ptr<Entity> entity
			@param sf::Event::EventType event
		*/
		template <class C>
		WeakRef<CommandInput> Bind(
			WeakRef<Entity> l_entity, 
			sf::Event::EventType l_event
		);



		/*
			@brief Binds a command input type to a container that will be called as a callback
			whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
			In this case, an event type will be passed.
			The execute command will be called when the current sfml event matches with the event passed as a parameter.
			@param std::weak_ptr<Entity> entity
			@param sf::Event::EventType event
		*/
		template <class C>
		WeakRef<CommandInput> Bind(
			sf::Event::EventType l_event,
			sf::Keyboard::Key l_key = sf::Keyboard::Unknown, 
			sf::Mouse::Button l_mouse = sf::Mouse::ButtonCount
		);



		/*
			@brief Gets size of the container
			@returns unsigned int size
		*/
		unsigned int GetSize();


		/*
			@brief
		*/
		auto& GetKeys() { return m_keys; }



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
	inline WeakRef<CommandInput> EventManager::Bind(sf::Keyboard::Key l_keyCode, const bool& l_isHold){
		for (auto& itr : m_keys)
			if (itr->GetKeyCode() == l_keyCode &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->SetSharedData(true);					//Setting shared data to true
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
	inline WeakRef<CommandInput> EventManager::Bind(sf::Mouse::Button l_mouseButton, const bool& l_isHold){
		for (auto& itr : m_keys)
			if (itr->GetMouseCode() == l_mouseButton &&							//Checking if command is already in memory
				typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->isHold() == l_isHold) {
				return itr->GetCommand();
			}

		auto newKey = MakeRef<CommandKey>();								//If not in memory, create one
		newKey->BindCommand<C>();											//Binding and creating command input
		newKey->GetCommand().lock()->SetSharedData(true);			        //Setting shared data to true
		newKey->SetMouseCode(l_mouseButton);								//Binding key code to command input
		newKey->SetHold(l_isHold);
		m_keys.push_back(std::move(newKey));								//Transfering ownership to container
		return m_keys.back()->GetCommand();
	}



	/*
		@brief Definition. Binds a command input type to a container that will be called as a callback
		whenever the key, mouse, or joystick is pressed (execute) or released (undo.)
		In this case, an entity pointer with an event type will be passed.
		The execute command will be called when the current sfml event matches with the event passed as a parameter.
		This method is useful when there's something to be done with said entity if said event is happening.
		@param std::weak_ptr<Entity> entity
		@param sf::Event::EventType event
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(WeakRef<Entity> l_entity, sf::Event::EventType l_event){
		for (auto& itr : m_keys)
			if (typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->GetEventType() == l_event)
				return itr->GetCommand();

		auto newKey = MakeRef<CommandKey>();
		newKey->BindCommand<C>();
		newKey->GetCommand().lock()->BindEntity(l_entity);
		newKey->SetEventType(l_event);
		m_keys.push_back(std::move(newKey));
		return m_keys.back()->GetCommand();
	}



	/*
		@brief
	*/
	template<class C>
	inline WeakRef<CommandInput> EventManager::Bind(sf::Event::EventType l_event, sf::Keyboard::Key l_key, sf::Mouse::Button l_mouse){
		for (auto& itr : m_keys)
			if (typeid(C) == typeid(*itr->GetCommand().lock()) &&
				itr->GetEventType() == l_event)
				return itr->GetCommand();

		auto newKey = MakeRef<CommandKey>();
		newKey->BindCommand<C>();
		newKey->SetEventType(l_event);
		newKey->SetKeyCode(l_key);
		newKey->SetMouseCode(l_mouse);
		m_keys.push_back(std::move(newKey));
		return m_keys.back()->GetCommand();
	}


}