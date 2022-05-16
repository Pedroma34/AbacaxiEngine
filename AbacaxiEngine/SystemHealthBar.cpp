



/*
	SystemHealthBar.h
	Purpose: System that enables entity to have a health bar above or below them.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/




#include "pch.h"
#include "Systems.h"	//Already includes SystemHealthBar.h
#include "Entity.h"
#include "Window.h"


namespace abx {




	/*_______________________________________________________*/
	SystemHealthBar::SystemHealthBar() :
		m_shape()
	{}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::Update(const float& l_time){

		/*Systems*/
		m_healthSystem = m_entity->GetSystem<SystemHealth>();	//If entity doesn't have a health system, abort this shit
		if (m_healthSystem.expired())
			return;
		m_spriteSystem = m_entity->GetSystem<SystemSprite>();
		if (m_spriteSystem.expired())
			return;

		/*Update Bar*/
		UpdatePosition(l_time);
		UpdateSize(l_time);

	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::Render(){
		SharedData::Window()->Draw(&m_shape);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::SetColor(const sf::Color& l_color){
		m_shape.setFillColor(l_color);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::SetOutlineThickness(float l_thickness){
		m_shape.setOutlineThickness(l_thickness);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::SetOutlineColor(const sf::Color& l_color){
		m_shape.setOutlineColor(l_color);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	sf::RectangleShape* SystemHealthBar::GetShape(){
		return &m_shape;
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::UpdatePosition(const float& l_time){

		auto spriteSys = m_spriteSystem.lock();				   //No need to check if it's valid because we already did

		/*Variables*/
		const auto& entityPos  =  spriteSys->GetPosition();
		const auto& entitySize =  spriteSys->GetSize();

		/*Logic*/
		m_shape.setPosition(								   //Making bar follow entity
			entityPos.x,
			entityPos.y - entitySize.y / 3
		);

	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemHealthBar::UpdateSize(const float& l_time){

		auto healthSys = m_healthSystem.lock();					   //No need to validate since we already did
		auto spriteSys = m_spriteSystem.lock();

		if (healthSys->GetHealth() < 0)							   //No need to update size
			return;

		/*Variables*/
		const auto& winSize     = SharedData::Window()->GetSize();
		const auto& entitySize  = spriteSys->GetSize();

		/*Logic*/
		m_shape.setSize(											//Resizing bar in relation to health
			sf::Vector2f(
				(entitySize.x * 0.5) * 
				(healthSys->GetHealth() / 100),
				winSize.x * 0.005
			)
		);
		m_shape.setOrigin(
			m_shape.getGlobalBounds().width / 2, 
			m_shape.getGlobalBounds().height / 2
		);

	}
	/*_______________________________________________________*/




}