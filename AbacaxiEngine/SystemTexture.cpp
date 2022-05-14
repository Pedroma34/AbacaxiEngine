

/*
	SystemTexture.cpp
	Purpose: Texture component for entities.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/





#include "pch.h"
#include "SystemTexture.h"



namespace abx {




	/*____________________________________________________________*/
	SystemTexture::SystemTexture() : 
		m_texture  (),
		m_chuckSize()
	{}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	SystemTexture::~SystemTexture(){}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	void SystemTexture::SetChunckSize(const sf::Vector2f& l_size){
		m_chuckSize = l_size;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	void SystemTexture::SetTexture(Ref<sf::Texture> l_texture){
		m_texture = l_texture;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	WeakRef<sf::Texture> SystemTexture::GetTexture(){
		return m_texture;
	}
	/*____________________________________________________________*/




	/*____________________________________________________________*/
	const sf::Vector2f& SystemTexture::GetChunckSize() const{
		return m_chuckSize;
	}
	/*____________________________________________________________*/





}