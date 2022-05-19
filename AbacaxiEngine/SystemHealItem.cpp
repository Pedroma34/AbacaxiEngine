



/*
	SystemHealItem.cpp
	Purpose: Healing ability component for entities (normally items).
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/




#include "pch.h"
#include "SystemHealItem.h"




namespace abx {




	/*_________________________________________________________________*/
	SystemHealItem::SystemHealItem() : 
		m_healValue(0)
	{}
	/*_________________________________________________________________*/




	/*_________________________________________________________________*/
	void SystemHealItem::SetHealValue(float l_healValue){
		m_healValue = l_healValue;
	}
	/*_________________________________________________________________*/




	/*_________________________________________________________________*/
	const float& SystemHealItem::GetHealValue() const{
		return m_healValue;
	}
	/*_________________________________________________________________*/





}