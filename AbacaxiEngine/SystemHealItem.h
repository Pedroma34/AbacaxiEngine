#pragma once
#pragma once



/*
	SystemHealItem.h
	Purpose: Healing ability component for entities (normally items).
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Healing ability component for entities (normally items).
	*/
	class SystemHealItem : public System {



		float m_healValue;			//By how much it's healing the entity



	public:



		/*
			@brief Constructor
		*/
		SystemHealItem();



		/*
			@brief Sets heal value
			@param float heal value
		*/
		void SetHealValue(float l_healValue);



		/*
		 @brief Gets heal value
		 @returns const float& healValue
		*/
		const float& GetHealValue() const;



	};



}