#pragma once



/*
	CommandSelectEntity.h
	Purpose: Command callback that selects an entity that touches the mouse
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that selects an entity that touches the mouse
	*/
	class CommandSelectEntity : public CommandInput {
	public:



		/*
			@brief Executes using shared data
		*/
		void Execute() override;



	};



}