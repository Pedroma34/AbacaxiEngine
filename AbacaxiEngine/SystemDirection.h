#pragma once



/*
	SystemDirection.h
	Purpose: Direction component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Direction enumaration
	*/
	enum class Direction { Right = 1, Left, Up, Down };



	/*
		@brief Component holds a entity's direction
	*/
	class SystemDirection : public System {



		Direction   m_direction;		//Direction that entity is facing
		bool		m_inverted;			//False if original texture is facing right, true if it's facing left



	public:



		/*
			@brief Constructor
		*/
		SystemDirection();



		/*
			@brief Updates system using app's time as seconds
			@param const float& time (seconds)
		*/
		virtual void Update(const float& l_time) override;



		/*
			@brief Set's entity's directoin
			@param const Diractoin& direction
		*/
		void SetDirection(const Direction& l_direction);



		/*
			@brief Dictates if entity is inverted. False if texture is facing right and
			true if it's facing left.
			@param const bool& direction
		*/
		void SetInverted(const bool& l_inverted);



		/*
			@brief Gets true if entity is inverted (texture facing left) or 
			false if it's not inverted (texture facing right)
			@returns const bool& inverted
		*/
		const bool& GetInverted() const;



		/*
			@brief Gets entity's direction
			@returns const Directoin& direction
		*/
		const Direction& GetDirection();



		/*
			@brief Gets entity's direction as a string
			@returns const std::string& directionString
		*/
		std::string GetDirectonString() const;



	};



}