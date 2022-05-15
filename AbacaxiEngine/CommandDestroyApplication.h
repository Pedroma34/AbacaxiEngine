#pragma once



/*
	CommandDestroyApplication.h
	Purpose: Command callback that destroys application. 
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "CommandInput.h"



namespace abx {



	/*
		@brief Command callback that destroys application.
	*/
	class CommandDestroyApplication : public CommandInput {
	public:



		/*
			@brief Executes using shared data 
		*/
		void Execute() override;




	};



}