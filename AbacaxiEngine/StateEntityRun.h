#pragma once


/*
	StateEntityRun.h
	Purpose: Modifies entity when in running state.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "StateEntity.h"

namespace abx {



	/*
		@brief Modifies entity when in running state
	*/
	class StateEntityRun : public StateEntity {
	public:



		/*
			@brief Constructor
		*/
		StateEntityRun();



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		void Update(const float& l_time) override;



	};

}