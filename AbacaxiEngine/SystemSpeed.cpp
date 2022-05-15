



/*
	SystemSpeed.h
	Purpose: Speed component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "SystemSpeed.h"




namespace abx {




	/*________________________________________________*/
	SystemSpeed::SystemSpeed() : 
		m_speed(0),
		m_maxSpeed(0)
	{}
	/*________________________________________________*/




	/*________________________________________________*/
	void SystemSpeed::SetSpeed(const float& l_speed){
		m_speed = l_speed;
	}
	/*________________________________________________*/




	/*________________________________________________*/
	void SystemSpeed::SetMaxSpeed(const float& l_maxSpeed){
		m_maxSpeed = l_maxSpeed;
	}
	/*________________________________________________*/




	/*________________________________________________*/
	const float& SystemSpeed::GetSpeed() const{
		return m_speed;
	}
	/*________________________________________________*/




	/*________________________________________________*/
	const float& SystemSpeed::GetMaxSpeed() const{
		return m_maxSpeed;
	}
	/*________________________________________________*/




}