#pragma once


/*
	StateEntityAttack.h
	Purpose: Modifies entity when in attack state.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "StateEntity.h"

namespace abx {



	/*
		@brief Modifies entity when in attack state.
	*/
	class StateEntityAttack : public StateEntity {
	public:



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		void Update(const float& l_time) override;



	};

}