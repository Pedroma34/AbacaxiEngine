#pragma once


/*
	StateEntityHurt.h
	Purpose: Modifies entity when in hurt state.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "StateEntity.h"

namespace abx {



	/*
		@brief Modifies entity when in hurt state.
	*/
	class StateEntityHurt : public StateEntity {
	public:



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		void Update(const float& l_time) override;



	};

}