


/*
	EntityBandit.h
	Purpose: An entity that holds various systems (components)
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "pch.h"
#include "EntityBandit.h"
#include "EntityManager.h"
#include "Window.h"
#include "Resources.h"



namespace abx {




	/*__________________________________________*/
	void EntityBandit::OnCreate() {

		/*Texture*/
		auto textureSys = AddSystem<SystemTexture>().lock();
		textureSys->SetTexture(
			SharedData::Resource()->AcquireTexture("Bandit")
		);
		textureSys->SetChunckSize({ 48,48 });

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
		spriteSys->SetScale({ 10,12 });									

		/*Animation*/
		auto animationSys = AddSystem<SystemAnimation>().lock();
		animationSys->AddAnimation("idle",       1,  1 , 4 , 0.7f );
		animationSys->AddAnimation("running",    1,  2 , 8 , 0.8f );
		animationSys->AddAnimation("attacking" , 1 , 3 , 8 , 0.5f );
		animationSys->AddAnimation("hit2",       1,  5 , 2 , 0.3f );
		animationSys->AddAnimation("dying",      1,  6 , 3 , 0.4f );

		/*State*/
		SetState<StateEntityIdle>();

		/*Speed*/
		auto speedSys = AddSystem<SystemSpeed>().lock();
		speedSys->SetSpeed(200.f);
		speedSys->SetMaxSpeed(speedSys->GetSpeed());

		/*Direction*/
		auto directionSys = AddSystem<SystemDirection>().lock();
		directionSys->SetDirection(Direction::Right);
		directionSys->SetInverted(true);							    //facing left

		/*Health*/
		auto healthSys = AddSystem<SystemHealth>().lock();
		healthSys->SetMaxHealth(100.f);
		healthSys->SetHealth(healthSys->GetMaxHealth());

		/*Health Bar*/
		auto barSys = AddSystem<SystemHealthBar>().lock();
		barSys->SetColor(sf::Color::Red);
		barSys->SetOutlineThickness(0.9f);
		barSys->SetOutlineColor(sf::Color::White);

		/*Killable*/
		AddSystem<SystemKillable>();

		/*Hit Box*/
		auto hitBoxSys = AddSystem<SystemHitBox>().lock();
		hitBoxSys->SetSize(
			spriteSys->GetSize().x / 1.8,
			spriteSys->GetSize().y
		);

		/*Damage*/
		auto damageSys = AddSystem<SystemDamage>().lock();
		damageSys->SetMaxDamage(10.f);
		damageSys->SetDamage(damageSys->GetMaxDamage());

		/*Damage Box*/
		auto damageBoxSys = AddSystem<SystemDamageBox>().lock();
		damageBoxSys->SetSize(
			spriteSys->GetSize().x / 3,
			spriteSys->GetSize().y
		);

	}
	/*__________________________________________*/





}
