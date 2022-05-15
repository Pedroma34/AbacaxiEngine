


/*
	CommandAttack.h
	Purpose: Command callback that makes an enity attack. Intended to be an SFML event
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/


#include "pch.h"
#include "CommandAttack.h"
#include "Entity.h"


namespace abx {




	/*_____________________________________________________________*/
	void CommandAttack::Execute(std::weak_ptr<Entity> l_entity) {
		auto entity = l_entity.lock();
		if (!entity)
			return;

		/*Systems*/
		auto spriteSys = entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto speedSys = entity->GetSystem<SystemSpeed>().lock();
		if (!speedSys)
			return;


		entity->SetState<StateEntityAttack>();			//Changing state


	}
	/*_____________________________________________________________*/

}