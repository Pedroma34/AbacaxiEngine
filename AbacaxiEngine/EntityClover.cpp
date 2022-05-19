



/*
	EntityClover.cpp
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/




#include "pch.h"
#include "EntityClover.h"
#include "Resources.h"



namespace abx {



	void EntityClover::OnCreate(){

		/*Texture*/
		auto textureSys = AddSystem<SystemTexture>().lock();
		textureSys->SetTexture(
			SharedData::Resource()->AcquireTexture("Clover")
		);
		textureSys->SetChunckSize({ 231,256 });

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
		spriteSys->SetScale({ 3,5 });

		/*Animation*/
		auto animationSys = AddSystem<SystemAnimation>().lock();
		animationSys->AddAnimation("idle", 1, 1, 6, 0.7f);

		/*State*/
		SetState<StateEntityIdle>();

		/*Direction*/
		auto directionSys = AddSystem<SystemDirection>().lock();
		directionSys->SetDirection(Direction::Right);
		directionSys->SetInverted(true);							    //facing left

		/*Health*/
		auto healthSys = AddSystem<SystemHealth>().lock();
		healthSys->SetMaxHealth(100.f);
		healthSys->SetHealth(healthSys->GetMaxHealth());

		/*Killable*/
		AddSystem<SystemKillable>();

		/*Hit Box*/
		auto hitBoxSys = AddSystem<SystemHitBox>().lock();
		hitBoxSys->SetSize(
			spriteSys->GetSize().x,
			spriteSys->GetSize().y
		);

		/*Heal Item*/
		auto healSys = AddSystem<SystemHealItem>().lock();
		healSys->SetHealValue(30.f);

	}


}