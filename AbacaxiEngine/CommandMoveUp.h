#pragma once



/*
	CommandMoveUp.h
	Purpose: Command callback that moves an entity up. Intended to be a "hold" event
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that moves an entity up. Intended to be a "hold" event
	*/
	class CommandMoveUp : public CommandInput {
	public:



		/*
			@brief Executes this with an entity
		*/
		void Execute(std::weak_ptr<Entity> l_entity) override;



		/*
			@brief Undoes this with an entity
		*/
		void Undo(std::weak_ptr<Entity> l_entity) override;



	};



}