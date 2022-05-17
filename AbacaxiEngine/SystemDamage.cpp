



/*
	SystemDamage.cpp
	Purpose: Damage component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/




#include "pch.h"
#include "SystemDamage.h"




namespace abx {




	/*_________________________________________________________*/
	SystemDamage::SystemDamage() : 
		m_maxDamage(0),
		m_damage(0)
	{}
	/*_________________________________________________________*/




	/*_________________________________________________________*/
	void SystemDamage::SetMaxDamage(float l_maxDamage){
		m_maxDamage = l_maxDamage;
	}
	/*_________________________________________________________*/




	/*_________________________________________________________*/
	void SystemDamage::SetDamage(float l_damage){
		m_damage = l_damage;
	}
	/*_________________________________________________________*/




	/*_________________________________________________________*/
	const float& SystemDamage::GetDamage() const{
		return m_damage;
	}
	/*_________________________________________________________*/




	/*_________________________________________________________*/
	const float& SystemDamage::GetMaxDamage() const{
		return m_maxDamage;
	}
	/*_________________________________________________________*/




}