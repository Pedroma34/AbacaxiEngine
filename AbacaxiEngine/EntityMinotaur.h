#pragma once


/*
	EntityMinotaur.h
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "Entity.h"




namespace abx {



	/*
		@brief Minotaur entity. Pocesses various components.
	*/
	class EntityMinotaur : public Entity {


	public:



		/*
			@brief Create function will be called when entity is created.
		*/
		void OnCreate() override;


		
	};


}