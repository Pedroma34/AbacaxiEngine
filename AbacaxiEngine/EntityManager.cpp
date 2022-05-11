

/*
	EntityManager.cpp
	Purpose: Manage, update, and render all entities, including systems (components) and states.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/



#include "pch.h"
#include "EntityManager.h"



namespace abx {




	/*______________________________________________________*/
	EntityManager::EntityManager(SharedData* l_sharedData) :
		m_entities(),
		m_toAdd(),
		m_collisionQueue(),
		m_toRemove(),
		m_id(0),
		m_sharedData(l_sharedData)
	{}
	/*______________________________________________________*/




	/*______________________________________________________*/
	EntityManager::~EntityManager() {}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::Update(const float& l_time){
		CollisionCheck(l_time);
		m_collisionQueue.clear();

		for (auto& itr : m_entities) {
			itr.second->Update(l_time);
			/*if (auto killable = itr.second->GetSystem<KillableSystem>().lock()) {
				if (killable->isDead()) {
					auto dieState = itr.second->SwitchLockState<DieState>().lock();
					if (dieState->hasPlayed())
						Remove(itr.second->GetId());
				}
			}*/
		}

	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::Render(){
		for (auto& itr : m_entities)
			itr.second->Render();
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::Remove(const unsigned int& l_toRemove){
		m_toRemove.push_back(l_toRemove);
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::LateUpdate(){

		for (auto& itr : m_entities)						//Entities late update, mainly erasing systems
			itr.second->LateUpdate();

		
		while (m_toAdd.begin() != m_toAdd.end()) {			//Adding entities in add queue
			CopyEntity(m_toAdd.begin()->second);
			m_toAdd.erase(m_toAdd.begin());
		}

		while (m_toRemove.begin() != m_toRemove.end()) {	//Deleting entities
			Delete(*m_toRemove.begin());
			m_toRemove.erase(m_toRemove.begin());
		}
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::PurgeEntities(){
		m_entities.clear();
		m_toAdd.clear();
		m_collisionQueue.clear();
		m_toRemove.clear();
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::CopyEntity(Ref<Entity>& l_entity){

		//Debug
		LogInfo(m_sharedData, "[ENTITY] New entity added from add queue: " + std::string(typeid(*l_entity).name()));

		m_entities.emplace_back(l_entity->GetId(), std::move(l_entity));
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::Delete(const unsigned int& l_id){
		for (auto itr = m_entities.begin(); itr != m_entities.end(); itr++) {
			if (itr->second->GetId() == l_id) {

				/////////////////////////////////////////////////////////////////////
					//Debug
				abx::LogWarn(m_sharedData, "[ENTITY] Entity removed from container: ["
					+ std::string(typeid(*itr->second).name()) + "]");
				/////////////////////////////////////////////////////////////////////

				m_entities.erase(itr);

				/////////////////////////////////////////////////////////////////////
					//Debug
				abx::LogInfo(m_sharedData, "[ENTITY] Entity container size: [" +
					std::string(std::to_string(m_entities.size())) + "]");
				/////////////////////////////////////////////////////////////////////

				return;
			}
		}
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::CollisionCheck(const float& l_time){
		for (auto entities = m_entities.begin(); entities != m_entities.end(); entities++)
			for (auto& itrCollision : m_collisionQueue) {

				if (entities->second.get() == itrCollision.first) {						//if this entity has a call in the queue...

					for (auto entities2 = m_entities.begin(); 
						entities2 != m_entities.end(); 
						entities2++) {

						if (entities->second->GetId() == entities2->second->GetId())	//if it's the same entity, skip it
							continue;

						itrCollision.second(entities2->second.get());					//calling the function and passing the next entity as an argument

					}
				}
			}
	}
	/*______________________________________________________*/
}