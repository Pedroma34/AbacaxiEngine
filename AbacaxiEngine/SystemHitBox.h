#pragma once



/*
	SystemHitBox.h
	Purpose: Hit box component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "System.h"



namespace abx {



	/*
		@brief Hit box component for entities
	*/
	class SystemHitBox : public System {



		sf::RectangleShape m_shape;		//Hit box shape that will be attached to entity



	public:



		/*
			@brief Constructor. Initialize hit box color
		*/
		SystemHitBox();



		/*
			@brief Updates component using app's time as seconds
			@param const float& time
		*/
		void Update(const float& l_time);



		/*
			@brief Renders hitbox if debug is on
		*/
		void Render() override;



		/*
			@brief Sets hit box color. Wrapper for sf::RectanglShape::setFillColor()
			@param const sf::Color& color
		*/
		void SetColor(const sf::Color& l_color);



		/*
			@brief Sets hit box size. Wrapper for sf::RectanglShape::setSize()
			@param const sf::Vector2f& size
		*/
		void SetSize(const sf::Vector2f& l_size);



		/*
			@brief Sets hit box size. Wrapper for sf::RectanglShape::setSize()
			@param const float size_x
			@param const float size_y
		*/
		void SetSize(float l_x, float l_y);



		/*
			@brief Gets hit box global bounds
			@returns const sf::FloatRect& global bounds
		*/
		const sf::FloatRect& GetGlobalBounds() const;



		/*
			@brief Gets hit box size
			@returns const sf::Vector2f& size
		*/
		const sf::Vector2f& GetSize() const;
		


		/*
			@brief Gets pointer to hit box shape
			@returns sf::RectangleShape* shape
		*/
		sf::RectangleShape* GetShape();



	};



}