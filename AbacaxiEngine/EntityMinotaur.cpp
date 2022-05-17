


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
			SharedData::Resource()->AcquireTexture("Minotaur")
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
		spriteSys->SetScale({ 20,24 });									//16% of the screen win the X axis and 20% of the screen in the Y axis

		/*Animation*/
		auto animationSys = AddSystem<SystemAnimation>().lock();
		animationSys->AddAnimation( "idle",	      1, 1, 5, 0.7f);
		animationSys->AddAnimation( "running",    1, 2, 8, 0.7f);
		animationSys->AddAnimation( "charging",   1, 3, 5, 0.7f);
		animationSys->AddAnimation( "attacking",  1, 4, 9, 0.5f);
		animationSys->AddAnimation( "attacking2", 1, 5, 5, 0.5f);
		animationSys->AddAnimation("stomp",       1, 6, 6, 0.7f);
		animationSys->AddAnimation("attacking3",  1, 7, 9, 0.7f);
		animationSys->AddAnimation("hit",         1, 8, 3, 0.4f);
		animationSys->AddAnimation("hit2",        1, 9, 3, 0.2f);
		animationSys->AddAnimation("dying",       1, 10, 6, 0.7f);

		/*State*/
		SetState<StateEntityIdle>();

		/*Speed*/
		auto speedSys = AddSystem<SystemSpeed>().lock();
		speedSys->SetSpeed(200.f);
		speedSys->SetMaxSpeed(speedSys->GetSpeed());

		/*Direction*/
		auto directionSys = AddSystem<SystemDirection>().lock();
		directionSys->SetDirection(Direction::Right);
		directionSys->SetInverted(false);							    //facing left

		/*Health*/
		auto healthSys = AddSystem<SystemHealth>().lock();
		healthSys->SetMaxHealth(100.f);
		healthSys->SetHealth(healthSys->GetMaxHealth());

		/*Health Bar*/
		auto barSys = AddSystem<SystemHealthBar>().lock();
		//barSys->SetColor(sf::Color::Red);
		barSys->SetOutlineThickness(1.0f);
		barSys->SetOutlineColor(sf::Color(255, 255, 255, 100));

		/*Killable*/
		AddSystem<SystemKillable>();

		/*Hit Box*/
		auto hitBoxSys = AddSystem<SystemHitBox>().lock();
		hitBoxSys->SetSize(
			spriteSys->GetSize().x / 2,
			spriteSys->GetSize().y / 2
		);

		/*Damage*/
		auto damageSys = AddSystem<SystemDamage>().lock();
		damageSys->SetMaxDamage(22.f);
		damageSys->SetDamage(damageSys->GetMaxDamage());

		/*Damage Box*/
		auto damageBoxSys = AddSystem<SystemDamageBox>().lock();
		damageBoxSys->SetSize(
			spriteSys->GetSize().x / 4,
			spriteSys->GetSize().y / 2
		);

	}
	/*__________________________________________*/





}
