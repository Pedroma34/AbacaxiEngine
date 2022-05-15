#pragma once



/*
	SystemSpeed.h
	Purpose: Speed component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/


#include "System.h"


namespace abx {


	/*
		@brief Component holds a floating speed and max speed for an entity.
	*/
	class SystemSpeed : public System {


		float m_speed;			//current entity's speed
		float m_maxSpeed;		//speed's cap


	public:



		/*
			@brief Constructor. Initialize members.
		*/
		SystemSpeed();



		/*
			@brief Changes entity's current speed.
			@param const float& speed
		*/
		void SetSpeed(const float& l_speed);



		/*
			@brief Changes entity's speed cap.
			@param const float& maxSpeed
		*/
		void SetMaxSpeed(const float& l_maxSpeed);



		/*
			@brief Gets entitiy's current speed.
			@returns const float& speed
		*/
		const float& GetSpeed() const;



		/*
			@brief Gets entitiy's speed cap.
			@returns const float& maxSpeed
		*/
		const float& GetMaxSpeed() const;



	};

}