#pragma once



/*
	CommandKey.h
	Purpose: CommandKey class holds necessery members for a callback using user's input through SFML events.
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "pch.h"
#include "CommandInput.h"



namespace abx {


	/*
		@brief Holds necessery members for a callback using user's input through SFML events.
		It is invoked through the event manager.
	*/
	class CommandKey : public Command{
	protected:



		Ref<CommandInput>  m_command;		//CommandKey's command input that will be bound in creatin inside event manager
		sf::Keyboard::Key  m_keyCode;		//Support for keyboard
		sf::Mouse::Button  m_mouseCode;		//Support for mouse
		bool			   m_hold;			//Is key a hold event? False if it's a normal input event



	public:



		/*
			@brief
		*/
		CommandKey() :
			m_command	(nullptr),
			m_keyCode	(sf::Keyboard::Key::Unknown),
			m_mouseCode (sf::Mouse::Button::ButtonCount),
			m_hold		(false)
		{}



		/*
			@brief Executes command input. If entity is not nullptr, it executes command with an entity,
			if shared data is not nullptr, it executes command with a shared data pointer.
		*/
		void Execute() override {
			if (!m_command->GetEntity().expired())
				m_command->Execute(m_command->GetEntity());
			else if (m_command->GetSharedData())
				m_command->Execute(m_command->GetSharedData());
		}



		/*
			@brief Undoes command input. Normally called when keybaord is released. 
			If entity is not nullptr, it executes command with an entity,
			if shared data is not nullptr, it executes command with a shared data pointer.
		*/
		void Undo() override {
			if (!m_command->GetEntity().expired())
				m_command->Undo(m_command->GetEntity());
			else if (m_command->GetSharedData())
				m_command->Undo(m_command->GetSharedData());
		}



		/*
			@brief Binds a templated command input
		*/
		template <class T>
		void BindCommand() {
			m_command = MakeRef<T>();
		}



		/*
			@brief Sets a keyboard key code
			@param sf::Keyboard::Key keyCode
		*/
		void SetKeyCode(sf::Keyboard::Key l_keyCode) { 
			m_keyCode = l_keyCode; 
		}



		/*
			@brief Sets a mouse key code
			@param sf::Mouse::Button mouseCode
		*/
		void SetMouseCode(sf::Mouse::Button l_mouseCode) { 
			m_mouseCode = l_mouseCode;
		}



		/*
			@brief Sets a hold boolean.
			@param const bool& hold
		*/
		void SetHold(const bool& l_hold) {
			m_hold = l_hold;
		}



		/*
			@brief Gets the key code.
			@returns sf::Keyboard::Key keyCode
		*/
		sf::Keyboard::Key GetKeyCode() const { 
			return m_keyCode; 
		}



		/*
			@brief Gets the mouse code.
			@returns sf::Mouse::Button mouseCode
		*/
		sf::Mouse::Button GetMouseCode() const { 
			return m_mouseCode; 
		}



		/*
			@brief Gets if command is a hold event
			@returns const bool& hold
		*/
		const bool& isHold() const { 
			return m_hold; 
		}



		/*
			@brief Gets a weak pointer to bound command input
			@returns std::weak_ptr<CommandInput> commandInput
		*/
		WeakRef<CommandInput> GetCommand() { 
			return m_command;
		}



	};



}