



/*
	CommandSelectEntity.h
	Purpose: Command callback that selects an entity that touches the mouse
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/




#include "pch.h"
#include "CommandSelectEntity.h"
#include "EntityManager.h"
#include "Window.h"



namespace abx {



	/*____________________________________________*/
	void CommandSelectEntity::Execute(){

		if (SharedData::EntityMgr()->GetSize() == 0 || 
			!SharedData::Debug())
			return;

		sf::Vector2f mousePos = SharedData::Window()->GetWindow()->mapPixelToCoords(
			sf::Mouse::getPosition(*SharedData::Window()->GetWindow())
		);

		auto& container = SharedData::EntityMgr()->GetEntityContainer();

		for (auto& itr : container) {
			auto hitBoxSys = itr.second->GetSystem<SystemHitBox>().lock();
			if (!hitBoxSys)
				continue;
			const auto& hitBoxBounds = hitBoxSys->GetGlobalBounds();
			if (hitBoxBounds.contains(mousePos))
				Debug::SetSelectedEntity(itr.second);
			
		}

	}
	/*____________________________________________*/




}

