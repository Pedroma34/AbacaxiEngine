



/*
	CommandKillEntity.cpp
	Purpose: Command callback that kills an entity if this entity has killable component
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/




#include "pch.h"
#include "CommandKillEntity.h"
#include "Entity.h"



namespace abx {




	/*__________________________________________________________________*/
	void CommandKillEntity::Execute(std::weak_ptr<Entity> l_entity){

		auto entity = l_entity.lock();
		if (!entity)
			return;

		auto killSys = entity->GetSystem<SystemKillable>().lock();
		if (!killSys)
			return;

		killSys->Kill();

	}
	/*__________________________________________________________________*/




}