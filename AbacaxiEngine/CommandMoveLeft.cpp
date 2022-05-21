



/*
	CommandMoveLeft.h
	Purpose: Command callback that moves an entity to the left. Intended to be a "hold" event
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/




#include "pch.h"
#include "CommandMoveLeft.h"
#include "Entity.h"



namespace abx {




	/*_____________________________________________________________*/
	void CommandMoveLeft::Execute(std::weak_ptr<Entity> l_entity) {
		auto entity = l_entity.lock();
		if (!entity)
			return;
		if (!entity->IsInState<StateEntityDie>().expired() ||
			!entity->IsInState<StateEntityHurt>().expired())
			return;

		/*Systems*/
		auto spriteSys = entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto speedSys = entity->GetSystem<SystemSpeed>().lock();
		if (!speedSys)
			return;


		auto state = entity->SetState<StateEntityRun>().lock();			//Changing state

		const auto& speed = speedSys->GetSpeed();
		const auto& time = *SharedData::Time();

		spriteSys->SetPosition(											//Moving entity
			spriteSys->GetPosition().x - speed * time.asSeconds(),
			spriteSys->GetPosition().y
		);

		/*Direction*/
		auto directionSystem = entity->GetSystem<SystemDirection>().lock();
		if (directionSystem)
			directionSystem->SetDirection(Direction::Left);
	}
	/*_____________________________________________________________*/




	/*_____________________________________________________________*/
	void CommandMoveLeft::Undo(std::weak_ptr<Entity> l_entity) {
		if (m_entity.expired())
			return;
		m_entity.lock()->SetState<StateEntityIdle>();
	}
	/*_____________________________________________________________*/




}
