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
		SharedData*					m_sharedData;	//weak pointer to app's shared data that might or might not be used in command



	public:


		
		/*
			@brief Constructor
		*/
		CommandInput() : 
			m_entity(WeakRef<Entity>()),
			m_sharedData(nullptr)
		{}



		/*
			@brief Binds entity to command
			@param std::weak_ptr entity
		*/
		void BindEntity(WeakRef<Entity> l_entity) {
			m_entity = l_entity; 
		}



		/*
			@brief Binds shared data to command
			@param SharedData* sharedData
		*/
		void BindSharedData(SharedData* l_sharedData) { 
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
			@brief Gets shared data bound to command
			@returns SharedData* sharedData
		*/
		SharedData* GetSharedData() {
			return m_sharedData; 
		}



	};



}