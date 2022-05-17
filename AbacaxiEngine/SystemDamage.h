#pragma once



/*
	SystemDamage.h
	Purpose: Damage component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Damage component for entities
	*/
	class SystemDamage : public System {



		float m_maxDamage;
		float m_damage;



	public:



		/*
			@brief Constructor
		*/
		SystemDamage();



		/*
			@brief Sets max damage
			@param float maxDamage
		*/
		void SetMaxDamage(float l_maxDamage);



		/*
			@brief Sets damage
			@param float damage
		*/
		void SetDamage(float l_damage);



		/*
			@brief Gets damage
			@returns const float& damage
		*/
		const float& GetDamage() const;



		/*
			@brief Gets max damage
			@returns const float& max damage
		*/
		const float& GetMaxDamage() const;



	};



}