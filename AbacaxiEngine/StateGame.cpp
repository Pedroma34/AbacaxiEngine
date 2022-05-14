

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

		//Testing entities//
		auto entity = m_sharedData->m_entityMgr->Add<EntitySquare>().lock();
		m_sharedData->m_entityMgr->Remove(entity->GetId());

		Ref<Entity> newEntity = MakeRef<Entity>();
		newEntity->BindSharedData(m_sharedData);
		auto recSystem = newEntity->AddSystem<SystemRectangleShape>().lock();
		recSystem->GetShape()->setFillColor(sf::Color::Blue);
		m_sharedData->m_entityMgr->Add(newEntity).lock()->GetId();
		//////////////////////////////////////////////////////////////////////

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
