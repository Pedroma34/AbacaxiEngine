



/*
	CommandPickUpItem.h
	Purpose: Command callback that makes an enity pick up an item around it.
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	19/May/2022
*/




#include "pch.h"
#include "CommandPickUpItem.h"
#include "Entity.h"
#include "EntityManager.h"



namespace abx {




	/*___________________________________________________________________*/
	void CommandPickUpItem::Execute(std::weak_ptr<Entity> l_entity){
		auto entity = l_entity.lock();
		if (!entity)
			return;

		/*Systems*/
		auto healthSys = entity->GetSystem<SystemHealth>().lock();
		if (!healthSys)
			return;
		auto hitBoxSys = entity->GetSystem<SystemHitBox>().lock();
		if (!hitBoxSys)
			return;
		
		/*Variables*/
		const auto&  health          = healthSys->GetHealth();
		const auto&  maxHealth       = healthSys->GetMaxHealth();
		const auto&  globalBounds    =  hitBoxSys->GetShape()->getGlobalBounds     ();
		auto&        entityContainer =  SharedData::EntityMgr()->GetEntityContainer();

		/*Logic*/
		for (auto& itr : entityContainer) {

			auto& collider = itr.second;											 //Entity that we want to compare

			if (collider->GetId() == entity->GetId())								 //Don't compare with this entity
				continue;

			/*Systems*/
			auto colliderHealItemSys = collider->GetSystem<SystemHealItem>().lock();
			if (!colliderHealItemSys)
				continue;
			auto colliderHitBoxSys = collider->GetSystem<SystemHitBox>().lock();
			if (!colliderHitBoxSys)
				continue;

			/*Variables*/
			const auto& colliderGlobalBounds = colliderHitBoxSys->GetGlobalBounds();
			const auto& healValue            = colliderHealItemSys->GetHealValue();

			/*Logic*/
			if (globalBounds.intersects(colliderGlobalBounds)) {
				if (health != maxHealth) {
					float result = health + healValue;
					if (result > maxHealth)
						healthSys->SetHealth(maxHealth);
					else
						healthSys->SetHealth(result);

					SharedData::EntityMgr()->Remove(collider->GetId());
				}
				break;
			}

		}

	}
	/*___________________________________________________________________*/




}