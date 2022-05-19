#pragma once



/*
	CommandMouseMoved.h
	Purpose: Command callback that executes when mouse has moved
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that executes when mouse has moved
	*/
	class CommandMouseMoved : public CommandInput {
	public:



		/*
			@brief Executes this with an event type
		*/
		void Execute(sf::Event l_event) override;




	};



}