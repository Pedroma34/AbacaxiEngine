#pragma once



/*
	CommandZoom.h
	Purpose: Command callback that zooms in or out of view
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	22/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that zooms in or out of view
	*/
	class CommandZoom : public CommandInput {
	public:



		/*
			@brief Executes using shared data
		*/
		void Execute(sf::Event l_event) override;



	};



}