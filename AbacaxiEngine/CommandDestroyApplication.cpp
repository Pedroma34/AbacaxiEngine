



/*
	CommandDestroyApplication.h
	Purpose: Command callback that destroys application.
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/


#include "pch.h"
#include "CommandDestroyApplication.h"
#include "Window.h"



namespace abx {



	/*________________________________________________________*/
	void CommandDestroyApplication::Execute(){
		SharedData::Window()->DestroyApplication();
	}
	/*________________________________________________________*/




}