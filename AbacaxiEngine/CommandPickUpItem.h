#pragma once



/*
	CommandPickUpItem.h
	Purpose: Command callback that makes an enity pick up an item around it.
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that makes an enity pick up an item around it.
	*/
	class CommandPickUpItem : public CommandInput {
	public:



		/*
			@brief Executes this with an entity
		*/
		void Execute(std::weak_ptr<Entity> l_entity) override;




	};



}