



/*
	CommandMouseMoved.h
	Purpose: Command callback that executes when mouse has moved
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/




#include "pch.h"
#include "CommandMouseMoved.h"
#include "Window.h"




namespace abx {




	/*_________________________________________________________________*/
	void CommandMouseMoved::Execute(sf::Event l_event){
		
		Debug::SetLastMousePos(sf::Vector2f(l_event.mouseMove.x, l_event.mouseMove.y));

	}
	/*_________________________________________________________________*/




}