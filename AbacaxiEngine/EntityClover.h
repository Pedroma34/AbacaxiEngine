#pragma once


/*
	EntityClover.h
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/



#include "Entity.h"




namespace abx {



	/*
		@brief Clover entity. Pocesses various components.
	*/
	class EntityClover : public Entity {


	public:



		/*
			@brief Create function will be called when entity is created.
		*/
		void OnCreate() override;



	};


}