

/*
	StateGame.cpp
	Purpose: Game machine state that will update and render game's logic.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"
#include "StateGame.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Window.h"
#include "EventManager.h"
#include "CommandInputs.h"


namespace abx {




	/*_________________________________________________________________________*/
	StateGame::StateGame(){}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	StateGame::~StateGame(){
		//Debugging
		LogWarn(
			"[STATE] Machine state destroyed: [" +
			std::string(typeid(*this).name()) + "]"
		);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::OnCreate(){

		/*Variables*/
		const auto& winSize   =  SharedData::Window()->GetSize();

		/*Entities*/
		auto player			  =  SharedData::EntityMgr()->Add<EntityMinotaur>().lock();
		auto playerSpriteSys  =  player->GetSystem<SystemSprite>().lock();
		playerSpriteSys->SetPosition(
			winSize.x / 2,
			winSize.y / 2
		);
		for (int i = 0; i < 3; i++) {
			auto enemy = SharedData::EntityMgr()->Add<EntityBandit>().lock();
			auto spriteSys = enemy->GetSystem<SystemSprite>().lock();
			spriteSys->SetPosition(
				rand() % winSize.x + 0,
				rand() % winSize.y + 0
			);
		}

		/*Events*/
		SharedData::EventMgr()->Bind<CommandMoveRight>  (player, sf::Keyboard::D,     true);
		SharedData::EventMgr()->Bind<CommandMoveLeft>   (player, sf::Keyboard::A,     true);
		SharedData::EventMgr()->Bind<CommandMoveUp>     (player, sf::Keyboard::W,     true);
		SharedData::EventMgr()->Bind<CommandMoveDown>	(player, sf::Keyboard::S,     true);
		SharedData::EventMgr()->Bind<CommandAttack>     (player, sf::Keyboard::Space, false);
		SharedData::EventMgr()->Bind<CommandKillEntity> (player, sf::Keyboard::Num1,  false);

		SharedData::EventMgr()->Bind<CommandDestroyApplication>	( sf::Keyboard::F1, false);
		SharedData::EventMgr()->Bind<CommandDebug>				(sf::Keyboard::Tab, false);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::OnDestroy(){

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Activate(){

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Deactivate(){

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Update(const float& l_time){
		SharedData::EntityMgr()->Update(l_time);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Render(){
		SharedData::EntityMgr()->Render();
	}
	/*_________________________________________________________________________*/
}
