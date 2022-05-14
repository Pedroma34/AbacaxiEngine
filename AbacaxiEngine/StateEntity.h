#pragma once



/*
	StateEntity.h
	Purpose: Base class for all entity's states. States are objects that are meant to organize entity's condition.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "pch.h"


namespace abx {



	/*
		@brief Base class for all entity's states. States are objects that are meant to organize entity's condition.
		State is an object inside an entity, therefore entity owns its states.
	*/
	class StateEntity {
	protected:


		bool		   m_played;	//has state been played? Useful for some state types to control animation cycles.
		class Entity*  m_entity;	//pointer to the owner of the state.


	public:



		/*
			@brief Constructor. Initialize members.
		*/
		StateEntity() :
			m_played(false),
			m_entity(nullptr)
		{}



		/*
			@brief Destructor
		*/
		virtual ~StateEntity() {}



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		virtual void Update(const float& l_time) = 0;



		/*
			@brief Binds owner of the state.
			@param Entity* entity
		*/
		void BindEntity(Entity* l_entity) {
			m_entity = l_entity;
		}



		/*
			@brief Gets if state has played. Useful to control animations.
			@returns const bool& played
		*/
		const bool& GetPlayed() {
			return m_played;
		}
	};

}