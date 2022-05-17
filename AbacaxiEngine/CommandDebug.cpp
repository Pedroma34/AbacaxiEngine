



/*
	CommandDebug.h
	Purpose: Command callback that switches application's visual debug mode
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/




#include "pch.h"
#include "CommandDebug.h"




namespace abx {




	/*_______________________________________*/
	void CommandDebug::Execute(){
		SharedData::SetDebug(!SharedData::Debug());
	}
	/*_______________________________________*/




}