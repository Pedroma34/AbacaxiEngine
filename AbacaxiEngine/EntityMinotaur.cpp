


/*
	EntityMinotaur.cpp
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "pch.h"
#include "EntityMinotaur.h"
#include "EntityManager.h"
#include "Window.h"
#include "Resources.h"



namespace abx {




	/*__________________________________________*/
	EntityMinotaur::EntityMinotaur()
	{
	}
	/*__________________________________________*/




	/*__________________________________________*/
	EntityMinotaur::~EntityMinotaur(){}
	/*__________________________________________*/




	/*__________________________________________*/
	void EntityMinotaur::OnCreate(){

		/*Texture*/
		auto textureSys = AddSystem<SystemTexture>().lock();
		textureSys->SetTexture(
			m_sharedData->m_resources->AcquireTexture("Minotaur")
		);
		textureSys->SetChunckSize({ 96,96 });

		/*Sprite*/
		auto spriteSys = AddSystem<SystemSprite>().lock();
		spriteSys->SetTexture(*textureSys->GetTexture().lock());
		spriteSys->SetTextureRect(
			sf::IntRect(
				0,
				0,
				textureSys->GetChunckSize().x,
				textureSys->GetChunckSize().y
			)
		);
		spriteSys->SetOrigin(
			sf::Vector2f(
			spriteSys->GetGlobalBounds().width / 2,
			spriteSys->GetGlobalBounds().height / 2
			)
		);
		spriteSys->SetScale({ 16,20 });									//16% of the screen win the X axis and 20% of the screen in the Y axis

	}
	/*__________________________________________*/





}
