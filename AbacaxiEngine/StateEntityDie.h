#pragma once


/*
	StateEntityDie.h
	Purpose: Modifies entity when in dying state. Intended to be a lock state.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/



#include "StateEntity.h"



namespace abx {



	/*
		@brief Modifies entity when in dying state. Intended to be a lock state.
	*/
	class StateEntityDie : public StateEntity {



		bool m_done;		//has animation been played?



	public:



		/*
			@brief Updates state using time as seconds.
			@param const float& time
		*/
		void Update(const float& l_time) override;



	};

}