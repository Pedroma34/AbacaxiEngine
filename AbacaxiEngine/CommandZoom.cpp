



/*
	CommandZoomIn.cpp
	Purpose: Command callback that zooms view
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	22/May/2022
*/




#include "pch.h"
#include "CommandZoom.h"




namespace abx {




	/*_________________________________________*/
	void CommandZoom::Execute(sf::Event l_event){

		if (!SharedData::Debug())
			return;

		if (l_event.type == sf::Event::MouseWheelScrolled) {

			float delta = l_event.mouseWheelScroll.delta;
			if (delta > 0)
				SharedData::View().zoom(0.9);
			else
				SharedData::View().zoom(1.1);

		}

	}
	/*_________________________________________*/




}