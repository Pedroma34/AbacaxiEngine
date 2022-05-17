


/*
	StateEntityAttack.cpp
	Purpose: Modifies entity when in attack state.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/



#include "pch.h"
#include "StateEntityAttack.h"
#include "Entity.h"




namespace abx {




	/*_________________________________________________________________________*/
	void StateEntityAttack::Update(const float& l_time){

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
		std::string animation = "attacking";

		if (animationSys->HasAnimation(animation) && !m_played &&
			animationSys->GetCurrentAnimation() != animation){						 //Only plays once when state is created 
																					 //because this class will loop until the animation has been played in full
																					 //This is useful for weapons cool down (or fire rate)
			
			animationSys->PlayAnimation(animation);

			auto damageBoxSystem = m_entity->GetSystem<SystemDamageBox>().lock();
			if (!damageBoxSystem)
				return;

			damageBoxSystem->SolveCollisions();										 //Applying damage to all entities inside the damage box
			m_played = true;														 //Boolean to keep track if animation has played so we can switch to idle state
			
		}

		if (m_played && !animationSys->IsPlayingAnimation())						  //Chekcs if animation has played in full, then switch to idle state 
			m_entity->SetState<StateEntityIdle>();


	}
	/*_________________________________________________________________________*/




}