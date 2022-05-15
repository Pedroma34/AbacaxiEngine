#pragma once



/*
	CommandAttack.h
	Purpose: Command callback that makes an enity attack. Intended to be an SFML event
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that makes an enity attack. Intended to be an SFML event
	*/
	class CommandAttack : public CommandInput {
	public:



		/*
			@brief Executes this with an entity
		*/
		void Execute(std::weak_ptr<Entity> l_entity) override;




	};



}