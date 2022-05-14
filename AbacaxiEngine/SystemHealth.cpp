

/*
	SystemHealth.cpp
	Purpose: Health component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/


#include "pch.h"
#include "SystemHealth.h"

namespace abx {




	/*____________________________________________________________*/
	SystemHealth::SystemHealth() : 
		m_health(0),
		m_maxHealth(0)
	{}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	SystemHealth::~SystemHealth(){}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	void SystemHealth::SetHealth(const float& l_health){
		m_health = l_health;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	void SystemHealth::SetMaxHealth(const float& l_maxHealth){
		m_maxHealth = l_maxHealth;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	const float& SystemHealth::GetHealth() const{
		return m_health;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	const float& SystemHealth::GetMaxHealth() const{
		return m_maxHealth;
	}
	/*____________________________________________________________*/





}
