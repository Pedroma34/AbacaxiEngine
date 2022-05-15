

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
		LogWarn(m_sharedData,
			"[STATE] Machine state destroyed: [" +
			std::string(typeid(*this).name()) + "]"
		);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::OnCreate(){

		/*Variables*/
		const auto& winSize   =  m_sharedData->m_window->GetSize();

		/*Entities*/
		auto player			  =  m_sharedData->m_entityMgr->Add<EntityMinotaur>().lock();
		auto playerSpriteSys  =  player->GetSystem<SystemSprite>().lock();
		playerSpriteSys->SetPosition(
			winSize.x / 2,
			winSize.y / 2
		);

		/*Events*/
		auto evntMgr		   =  m_sharedData->m_eventMgr;
		evntMgr->Bind<CommandMoveRight> (player, sf::Keyboard::D,     true);
		evntMgr->Bind<CommandMoveLeft>  (player, sf::Keyboard::A,     true);
		evntMgr->Bind<CommandMoveUp>    (player, sf::Keyboard::W,     true);
		evntMgr->Bind<CommandMoveDown>	(player, sf::Keyboard::S,     true);
		evntMgr->Bind<CommandAttack>    (player, sf::Keyboard::Space, false);
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
		m_sharedData->m_entityMgr->Update(l_time);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateGame::Render(){
		m_sharedData->m_entityMgr->Render();
	}
	/*_________________________________________________________________________*/
}
