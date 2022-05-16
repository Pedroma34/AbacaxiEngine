#pragma once



/*
	SystemKillable.h
	Purpose: Allows entities to be killable and removed if health reaches zero.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Allows entities to be killable and removed if health reaches zero.
	*/
	class SystemKillable : public System {

		

	public:



		/*
			@brief Updates component using app's time as seconds.
			@param cosnt float& time
		*/
		void Update(const float& l_time) override;



		/*
			@brief Setting health to zero
		*/
		void Kill();



	};

}