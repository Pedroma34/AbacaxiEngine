#pragma once



/*
	CommandDebug.h
	Purpose: Command callback that switches application's visual debug mode
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that switches application's visual debug mode
	*/
	class CommandDebug : public CommandInput {
	public:



		/*
			@brief Executes using shared data
		*/
		void Execute() override;



	};



}