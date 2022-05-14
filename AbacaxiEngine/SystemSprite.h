#pragma once



/*
	SystemSprite.h
	Purpose: Sprite component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "System.h"



namespace abx {



	/*
		@brief Comoponent holds a sprite and sprite's scale relative to the window.
		A wrapper for sf::Sprite
	*/
	class SystemSprite : public System {


		sf::Sprite    m_sprite;	 //entity's sprite
		sf::Vector2f  m_scale;	 //scale in percentage relative to window's size


	public:



		/*
			@brief Constructor. Initialize members.
		*/
		SystemSprite();



		/*
			@brief Destructor.
		*/
		~SystemSprite();




		/*
			@brief Renders sprite.
		*/
		void Render() override;




		/*
			@brief Sets sprite's position. sf::Sprite::setPosition wrapper
			@oaram const sf::Vector2f& position
		*/
		void SetPosition(const sf::Vector2f& l_pos);



		/*
			@brief Sets sprite's position. sf::Sprite::setPosition wrapper
			@oaram const x& position
			@oaram const y& position
		*/
		void SetPosition(const float& l_x, const float& l_y);



		/*
			@brief Sets sprite's position. sf::Sprite::setColor wrapper
			@param const sf::Color& color
		*/
		void SetColor(const sf::Color& l_color);




		/*
			@brief Scales sprite relative to the window. l_percentage is how big is the sprite compared to the size of the window.
			ex: 50 is going to be 50% of the window.
			@oaram const sf::Vector2f& percentage
			@returns size of the sprite in pixels
		*/
		sf::Vector2f SetScale(const sf::Vector2f& l_percentage);



		/*
			@brief Sets sprite's texture. sf::Sprite::setTexture wrapper
			@param const sf::Texutre& texture
		*/
		void SetTexture(const sf::Texture& l_texture);



		/*
			@brief Sets sprite's texture rect. sf::Sprite::setTextureRect wrapper
			@param const sf::IntRect& rectangle
		*/
		void SetTextureRect(const sf::IntRect& l_rectangle);



		/*
			@brief Sets sprite's origin. sf::Sprite::setOrigin wrapper
			@param const sf::Vector2f& origin
		*/
		void SetOrigin(const sf::Vector2f& l_origin);



		/*
			@brief Gets a pointer to component's sprite.
			@returns sf::Sprite* sprite
		*/
		sf::Sprite* GetSprite();



		/*
			@brief Gets a reference to sprite's global bounds. sf::Sprite::getGlobalBounds wrapper
			@returns const sf::FloatRect& globalBounds
		*/
		const sf::FloatRect& GetGlobalBounds() const;



		/*
			@brief Gets a reference to component's scale. It is relative to the screen in percentage.
			@returns const sf::Vector2f& scale
		*/
		const sf::Vector2f& GetScale() const;



		/*
			@brief Gets a reference to sprite's size. Uses global bounds as a reference.
			@returns const sf::Vector2f& size
		*/
		const sf::Vector2f GetSize() const;



		/*
			@brief Gets a reference to sprite's position. sf::Sprite::getPosition wrapper.
			@returns const sf::Vector2f& position
		*/
		const sf::Vector2f& GetPosition() const;



	};



}