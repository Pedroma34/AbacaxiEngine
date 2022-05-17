

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
		auto enemy			  =  SharedData::EntityMgr()->Add<EntityBandit>().lock();
		auto enemySpriteSys   =  enemy->GetSystem<SystemSprite>().lock();
		enemySpriteSys->SetPosition(
			rand() % winSize.x + 0,
			rand() % winSize.y + 0
		);

		/*Player Events*/
		SharedData::EventMgr()->Bind<CommandMoveRight>  (player, sf::Keyboard::D,     true);
		SharedData::EventMgr()->Bind<CommandMoveLeft>   (player, sf::Keyboard::A,     true);
		SharedData::EventMgr()->Bind<CommandMoveUp>     (player, sf::Keyboard::W,     true);
		SharedData::EventMgr()->Bind<CommandMoveDown>	(player, sf::Keyboard::S,     true);
		SharedData::EventMgr()->Bind<CommandAttack>     (player, sf::Keyboard::Space, false);
		SharedData::EventMgr()->Bind<CommandKillEntity> (player, sf::Keyboard::Num1,  false);

		/*Enemy Events*/
		SharedData::EventMgr()->Bind<CommandMoveRight>  (enemy, sf::Keyboard::Right,    true);
		SharedData::EventMgr()->Bind<CommandMoveLeft>   (enemy, sf::Keyboard::Left,     true);
		SharedData::EventMgr()->Bind<CommandMoveUp>     (enemy, sf::Keyboard::Up,       true);
		SharedData::EventMgr()->Bind<CommandMoveDown>   (enemy, sf::Keyboard::Down,     true);
		SharedData::EventMgr()->Bind<CommandAttack>     (enemy, sf::Keyboard::Enter,    false);
		SharedData::EventMgr()->Bind<CommandKillEntity> (enemy, sf::Keyboard::Num2,     false);

		/*Data Eventss*/
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
