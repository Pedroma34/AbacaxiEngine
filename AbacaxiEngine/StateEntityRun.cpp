


/*
	StateEntityRun.cpp
	Purpose: Modifies entity when in running state.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "pch.h"
#include "StateEntityRun.h"
#include "Entity.h"


namespace abx {


	/*_____________________________________________*/
	StateEntityRun::StateEntityRun(){}
	/*_____________________________________________*/




	/*_____________________________________________*/
	void StateEntityRun::Update(const float& l_time){
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
		std::string animation = "running";
		if (animationSys->HasAnimation(animation))
			if (animationSys->GetCurrentAnimation() != animation)
				animationSys->PlayAnimation(animation);
	}
	/*_____________________________________________*/




}
