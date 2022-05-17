



/*
	SystemHitBox.cpp
	Purpose: Hit box component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "SystemHitBox.h"
#include "Entity.h"
#include "Window.h"




namespace abx {


	/*______________________________________________________________*/
	SystemHitBox::SystemHitBox() : 
		m_shape()
	{
		m_shape.setFillColor(sf::Color(255, 234, 0, 30));	//yellow transparent
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	void SystemHitBox::Update(const float& l_time){

		/*System*/
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;

		/*Variable*/
		const auto& entityPos = spriteSys->GetPosition();
		const auto& thisPos = m_shape.getPosition();

		/*Logic*/
		m_shape.setPosition(entityPos.x, entityPos.y);					//Attach to entity

	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	void SystemHitBox::Render(){

		const bool& debug = SharedData::Debug();
		if (debug)
			SharedData::Window()->Draw(&m_shape);		//Draw hitbox if debug is on
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	void SystemHitBox::SetColor(const sf::Color& l_color){
		m_shape.setFillColor(l_color);
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	void SystemHitBox::SetSize(const sf::Vector2f& l_size){
		m_shape.setSize(l_size);
		m_shape.setOrigin(
			m_shape.getSize().x / 2,
			m_shape.getSize().y / 2
		);

	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	void SystemHitBox::SetSize(float l_x, float l_y){
		m_shape.setSize(sf::Vector2f(l_x, l_y));
		m_shape.setOrigin(
			m_shape.getSize().x / 2,
			m_shape.getSize().y / 2
		);
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	const sf::FloatRect& SystemHitBox::GetGlobalBounds() const {
		return m_shape.getGlobalBounds();
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	const sf::Vector2f& SystemHitBox::GetSize() const {
		return m_shape.getSize();
	}
	/*______________________________________________________________*/




	/*______________________________________________________________*/
	sf::RectangleShape* SystemHitBox::GetShape(){
		return &m_shape;
	}
	/*______________________________________________________________*/




}