#pragma once



/*
	CommandKillEntity.h
	Purpose: Command callback that kills an entity if this entity has killable component
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that kills an entity if this entity has killable component
	*/
	class CommandKillEntity : public CommandInput {
	public:



		/*
			@brief Executes this with an entity
		*/
		void Execute(std::weak_ptr<Entity> l_entity) override;



	};



}