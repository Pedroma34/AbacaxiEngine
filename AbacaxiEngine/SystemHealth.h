#pragma once



/*
	SystemHealth.h
	Purpose: Health component for entities. 
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/


#include "System.h"


namespace abx {


	/*
		@brief Component holds a health and max health for an entity.
	*/
	class SystemHealth : public System {


		float m_health;			//current entity's health
		float m_maxHealth;		//health's cap


	public:



		/*
			@brief Constructor. Initialize members.
		*/
		SystemHealth();



		/*
			@brief Destructor.
		*/
		~SystemHealth();



		/*
			@brief Changes entity's current health.
			@param const float& health
		*/
		void SetHealth(const float& l_health);



		/*
			@brief Changes entity's health cap.
			@param const float& maxHealth
		*/
		void SetMaxHealth(const float& l_maxHealth);



		/*
			@brief Gets entitiy's current health.
			@returns const float& health
		*/
		const float& GetHealth() const;



		/*
			@brief Gets entitiy's health cap.
			@returns const float& maxHealth
		*/
		const float& GetMaxHealth() const;



	};

}