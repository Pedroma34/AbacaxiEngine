#pragma once



/*
	SystemHealthBar.h
	Purpose: System that enables entity to have a health bar above or below them.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/



#include "System.h"



namespace abx {


	/*
		@brief System that enables entity to have a health bar above or below them
	*/
	class SystemHealthBar : public System {



		sf::RectangleShape           m_shape;			 //Health bar's shape
		sf::RectangleShape	         m_fullHealth;		 //Full health bar's shape
		WeakRef<class SystemSprite>  m_spriteSystem;	 //Pointer to entity's sprite system
		WeakRef<class SystemHealth>  m_healthSystem;	 //Pointer to entity's health system



	public:



		/*
			@brief Constructor
		*/
		SystemHealthBar();



		/*
			@brief Updates system using app's time as seconds
			@param const float& time
		*/
		void Update(const float& l_time) override;



		/*
			@brief Render system's drawables
		*/
		void Render() override;



		/*
			@brief Wrapper for sf::Rectangle::setFillColor. Sets shape's color
			@param const sf::Color& color
		*/
		void SetColor(const sf::Color& l_color);



		/*
			@brief Wrapper for sf::Rectangle::setOutilneThickness
			@param float thickness
		*/
		void SetOutlineThickness(float l_thickness);



		/*
			@brief Wrapper for sf::Rectangle::setOutlineColor
			@param const sf::Color& color
		*/
		void SetOutlineColor(const sf::Color& l_color);



		/*
			@brief Returns a pointer to the shape of the health bar
			@returns sf::RectangleShape* shape
		*/
		sf::RectangleShape* GetShape();



	private:



		/*
			@brief Helper function to update the position of health bar every tick,
			spacially binding it to the entity
		*/
		void UpdatePosition(const float& l_time);



		/*
			@brief Helper function to update the size of health bar every tick,
			making it decrease if entity's health is decreased or vice-versa.
		*/
		void UpdateSize(const float& l_time);



	};



}