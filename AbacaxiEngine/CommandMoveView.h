#pragma once



/*
	CommandMoveView.h
	Purpose: Command callback that moves window view
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	21/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that moves window view
	*/
	class CommandMoveView : public CommandInput {
	public:



		/*
			@brief Executes command
		*/
		void Execute(sf::Event l_event) override;




	};



}