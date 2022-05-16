#pragma once


/*
	EntityBandit.h
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "Entity.h"




namespace abx {



	/*
		@brief Bandit entity. Pocesses various components.
	*/
	class EntityBandit : public Entity {


	public:



		/*
			@brief Create function will be called when entity is created.
		*/
		void OnCreate() override;



	};


}