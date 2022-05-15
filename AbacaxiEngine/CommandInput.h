#pragma once



/*
	CommandInput.h
	Purpose: Base class that allows various callbakcs with customs actions.
	Each command input is bound to a command key and managed in the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "Command.h"



namespace abx {



	/*
		@brief Base class that allows various callbakcs with customs actions.
		Each command input is bound to a command key and managed in the event manager.
	*/
	class CommandInput : public Command {
	protected:



		WeakRef<class Entity>		m_entity;		//weak pointer to an entity that might or might not be used in command
		bool						m_sharedData;	//Dictates if command is using shared data rather than an entity


	public:


		
		/*
			@brief Constructor
		*/
		CommandInput() : 
			m_entity(WeakRef<Entity>()),
			m_sharedData(false)
		{}



		/*
			@brief Binds entity to command
			@param std::weak_ptr entity
		*/
		void BindEntity(WeakRef<Entity> l_entity) {
			m_entity = l_entity; 
		}



		/*
			@brief Sets shared data boolean. If true, command will execute using shared data instead of entity.
		*/
		void SetSharedData(const bool& l_sharedData) {
			m_sharedData = l_sharedData;
		}



		/*
			@brief Gets entity bound to command
			@returns std::weak_ptr<Entity> entity
		*/
		WeakRef<Entity> GetEntity() { 
			return m_entity; 
		}



		/*
			@brief Gets shared data boolean
			@returns const bool& sharedData
		*/
		const bool& GetSharedData() {
			return m_sharedData; 
		}



	};



}