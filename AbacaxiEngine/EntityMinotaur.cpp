


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

		/*Animation*/
		auto animationSystem = AddSystem<SystemAnimation>().lock();
		animationSystem->AddAnimation( "idle",	     1, 1, 5, 0.7f);
		animationSystem->AddAnimation( "running",    1, 2, 8, 0.7f);
		animationSystem->AddAnimation( "charging",   1, 3, 5, 0.7f);
		animationSystem->AddAnimation( "attacking",  1, 4, 9, 0.5f);
		animationSystem->AddAnimation( "attacking2", 1, 5, 5, 0.5f);
		animationSystem->AddAnimation("stomp",       1, 6, 6, 0.7f);
		animationSystem->AddAnimation("attacking3",  1, 7, 9, 0.7f);
		animationSystem->AddAnimation("hit",         1, 8, 3, 0.4f);
		animationSystem->AddAnimation("hit2",        1, 9, 3, 0.2f);
		animationSystem->AddAnimation("dying",       1, 10, 6, 0.7f);

		/*State*/
		SetState<StateEntityIdle>();

	}
	/*__________________________________________*/





}
