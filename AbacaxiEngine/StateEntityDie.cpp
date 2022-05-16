


/*
	StateEntityDie.cpp
	Purpose: Modifies entity when in dying state. Intended to be a lock state.
	@author Pedro Sergio de Castro Sarmento Filho
	16/May/2022
*/



#include "pch.h"
#include "StateEntityDie.h"
#include "Entity.h"




namespace abx {




	/*_________________________________________________________________________*/
	void StateEntityDie::Update(const float& l_time) {

		/*Systems*/
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
		std::string animation = "dying";
		if (animationSys->HasAnimation(animation) &&
			!m_done) {

			animationSys->PlayAnimation(animation);
			m_done = true;

		}

		if (m_done && !animationSys->IsPlayingAnimation())
			m_played = true;


	}
	/*_________________________________________________________________________*/




}