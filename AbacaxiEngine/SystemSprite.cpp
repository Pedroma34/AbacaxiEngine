

/*
	SystemSprite.cpp
	Purpose: Sprite component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/





#include "pch.h"
#include "SystemSprite.h"
#include "Entity.h"
#include "Window.h"



namespace abx {




	/*_______________________________________________________*/
	void SystemSprite::Render() {
		m_entity->GetSharedData()->m_window->Draw(&m_sprite);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetPosition(const sf::Vector2f& l_pos) {
		m_sprite.setPosition(l_pos);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetPosition(const float& l_x, const float& l_y) {
		m_sprite.setPosition(l_x, l_y);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetColor(const sf::Color& l_color) {
		m_sprite.setColor(l_color);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	sf::Vector2f SystemSprite::SetScale(const sf::Vector2f& l_percentage) {

		//Variables//

		const auto& winSize = m_entity->GetSharedData()->m_window->GetSize();

		sf::Vector2f spriteSize(
			m_sprite.getGlobalBounds().width,
			m_sprite.getGlobalBounds().height
		);

		sf::Vector2f percentage(								//Current sprite size in percentage relative to the screen
			spriteSize.x * 100 / winSize.x,
			spriteSize.y * 100 / winSize.y
		);

		sf::Vector2f result(									//Calculates how much bigger it needs to be to fufill the l_percentage size
			winSize.x * l_percentage.x / 100 / spriteSize.x,
			winSize.y * l_percentage.y / 100 / spriteSize.y
		);

		//Logic//
		m_sprite.setScale(result.x, result.y);					//Aplying new scale

		m_scale = sf::Vector2f(result.x, result.y);				//Setting member to new scale

		return sf::Vector2f(m_sprite.getGlobalBounds().width,
			m_sprite.getGlobalBounds().height
		);

	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetTexture(const sf::Texture& l_texture){
		m_sprite.setTexture(l_texture);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetTextureRect(const sf::IntRect& l_rectangle){
		m_sprite.setTextureRect(l_rectangle);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	void SystemSprite::SetOrigin(const sf::Vector2f& l_origin){
		m_sprite.setOrigin(l_origin);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	sf::Sprite* SystemSprite::GetSprite() {
		return &m_sprite;
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	const sf::FloatRect& SystemSprite::GetGlobalBounds() const {
		return m_sprite.getGlobalBounds();
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	const sf::Vector2f& SystemSprite::GetScale() const {
		return m_scale;
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	const sf::Vector2f SystemSprite::GetSize() const {
		return sf::Vector2f(
			m_sprite.getGlobalBounds().width,
			m_sprite.getGlobalBounds().height
		);
	}
	/*_______________________________________________________*/




	/*_______________________________________________________*/
	const sf::Vector2f& SystemSprite::GetPosition() const{
		return m_sprite.getPosition();
	}
	/*_______________________________________________________*/






}
