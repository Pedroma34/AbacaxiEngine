#pragma once


/*
	StateEntityIdle.h
	Purpose: Modifies entity when in idle state.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "StateEntity.h"

namespace abx {



	/*
		@brief Modifies entity when in idle state
	*/
	class StateEntityIdle : public StateEntity {
	public:



		/*
			@brief Constructor
		*/
		StateEntityIdle();



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		void Update(const float& l_time) override;



	};

}