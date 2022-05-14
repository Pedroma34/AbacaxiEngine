


/*
	StateEntityIdle.cpp
	Purpose: Modifies entity when in idle state.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "StateEntityIdle.h"
#include "Entity.h"




namespace abx {


	/*_____________________________________________*/
	StateEntityIdle::StateEntityIdle() {}
	/*_____________________________________________*/




	/*_____________________________________________*/
	void StateEntityIdle::Update(const float& l_time) {
		/*System*/
		auto spriteSys = m_entity->GetSystem<SystemSprite>().lock();
		if (!spriteSys)
			return;
		auto textureSys = m_entity->GetSystem<SystemTexture>().lock();
		if (!textureSys)
			return;
		auto animationSys = m_entity->GetSystem<SystemAnimation>().lock();
		if (!animationSys)
			return;

		/*Animation*/
		std::string animation = "idle";
		if (animationSys->HasAnimation(animation))
			if (animationSys->GetCurrentAnimation() != animation)
				animationSys->PlayAnimation(animation);
	}
	/*_____________________________________________*/




}
