



/*
	SystemKillable.h
	Purpose: Allows entities to be killable and removed if health reaches zero.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/




#include "pch.h"
#include "SystemKillable.h"
#include "Entity.h"
#include "EntityManager.h"




namespace abx {




	/*______________________________________________________*/
	void SystemKillable::Update(const float& l_time){

		auto healthSys = m_entity->GetSystem<SystemHealth>().lock();
		if (!healthSys)
			return;

		const float& health = healthSys->GetHealth();

		if (health <= 0) {
			auto dieState = m_entity->SetLockState<StateEntityDie>().lock();		//Locking state so it can't be changed
			if (dieState->GetPlayed())												//If state has been played in full, remove entity
				SharedData::EntityMgr()->Remove(m_entity->GetId());
		}

	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void SystemKillable::Kill(){

		auto healthSys = m_entity->GetSystem<SystemHealth>().lock();
		if (!healthSys)
			return;

		healthSys->SetHealth(0);
	}
	/*______________________________________________________*/




}