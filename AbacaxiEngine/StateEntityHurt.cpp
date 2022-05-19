


/*
	StateEntityHurt.cpp
	Purpose: Modifies entity when in hurt state.
	@author Pedro Sergio de Castro Sarmento Filho
	17/May/2022
*/



#include "pch.h"
#include "StateEntityHurt.h"
#include "Entity.h"




namespace abx {




	/*_________________________________________________________________________*/
	void StateEntityHurt::Update(const float& l_time) {

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
		std::string animation = "hit2";

		if (animationSys->HasAnimation(animation) && !m_played) {						

			animationSys->PlayAnimation(animation);
			m_played = true;													  //Boolean to keep track if animation has played so we can switch to idle state
		
		}
		if(!animationSys->HasAnimation(animation))
			m_entity->SetState<StateEntityIdle>();								  //If it doens't have animation

		if (m_played && !animationSys->IsPlayingAnimation())					  //Chekcs if animation has played in full, then switch to idle state 
			m_entity->SetState<StateEntityIdle>();


	}
	/*_________________________________________________________________________*/




}