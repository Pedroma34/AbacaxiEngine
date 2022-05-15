



/*
	SystemDirection.cpp
	Purpose: Direction component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "SystemDirection.h"
#include "Entity.h"



namespace abx {
	/*_______________________________________________________________*/
	SystemDirection::SystemDirection() :
		m_direction(Direction::Right),
		m_inverted(false)
	{}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	void SystemDirection::Update(const float& l_time){
		
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;


		int inverted = m_inverted ? -1 : 1;

		switch (m_direction) {
		case Direction::Right:
			spriteSys->GetSprite()->setScale(spriteSys->GetScale().x * inverted, spriteSys->GetScale().y);	  //facing right
			break;
		case Direction::Left:
			spriteSys->GetSprite()->setScale(spriteSys->GetScale().x * -inverted, spriteSys->GetScale().y);   //facing left
			break;

		}
	}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	void SystemDirection::SetDirection(const Direction& l_direction){
		m_direction = l_direction;
	}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	void SystemDirection::SetInverted(const bool& l_inverted){
		m_inverted = l_inverted;
	}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	const bool& SystemDirection::GetInverted() const{
		return m_inverted;
	}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	const Direction& SystemDirection::GetDirection(){
		return m_direction;
	}
	/*_______________________________________________________________*/




	/*_______________________________________________________________*/
	std::string SystemDirection::GetDirectonString() const{
		switch (m_direction) {
		case Direction::Down:
			return "Down";
			break;
		case Direction::Left:
			return "Left";
			break;
		case Direction::Right:
			return "Right";
			break;
		case Direction::Up:
			return "Up";
			break;
		}
	}
	/*_______________________________________________________________*/




}
