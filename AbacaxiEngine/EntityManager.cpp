

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
		m_collisionQueue.clear();					//Since we add to the queue every tick, we need to free memory

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
	WeakRef<Entity> EntityManager::Add(Ref<Entity>& l_entity){
		l_entity->m_sharedData = m_sharedData;					//binding shared data
		l_entity->m_id = m_id;
		m_entities.emplace_back(m_id, std::move(l_entity));		//moving ownership to container. So "l_entity" will be empty
		m_id++;
		return m_entities.back().second;
	}




	/*______________________________________________________*/
	WeakRef<Entity> EntityManager::AddLate(Ref<Entity>& l_entity){
		l_entity->m_sharedData = m_sharedData;					//binding shared data
		l_entity->m_id = m_id;
		m_toAdd.emplace_back(m_id, std::move(l_entity));		//transfering ownership to container. So "l_entity" will be empty
		m_id++;
		return m_toAdd.back().second;
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::Remove(const unsigned int& l_toRemove){
		m_toRemove.push_back(l_toRemove);
	}
	/*______________________________________________________*/




	/*______________________________________________________*/
	void EntityManager::RemoveAll(){
		m_entities			.clear();
		m_toAdd				.clear();
		m_collisionQueue	.clear();
		m_toRemove			.clear();
	}




	/*______________________________________________________*/
	void EntityManager::LateUpdate(){

		for (auto& itr : m_entities)						//Entities late update, mainly erasing systems
			itr.second->LateUpdate();

		
		while (m_toAdd.begin() != m_toAdd.end()) {			//Adding entities in add queue
			CopyEntity(m_toAdd.begin()->second);			//Transfering ownership to container.
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
	WeakRef<Entity> EntityManager::Get(const unsigned int& l_id){
		for (auto& itr : m_entities)
			if (itr.second->m_id == l_id)
				return itr.second;

		return WeakRef<Entity>();
	}




	/*______________________________________________________*/
	unsigned int EntityManager::GetSize(){
		return m_entities.size();
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
		for (auto caller = m_entities.begin();											//Our "callers" entity
			caller != m_entities.end();
			caller++)

			for (auto& itrCollision : m_collisionQueue) {								//For each caller, we loop through collision queue

				if (!itrCollision.first.expired() && 
					caller->second.get() == itrCollision.first.lock().get()) 			//if this caller has a call in the queue...

					for (auto receiver = m_entities.begin();							//Our "receivers"
						receiver != m_entities.end();
						receiver++) {

					if (caller->second->GetId() == receiver->second->GetId())			//Making sure our caller doesn't perform logic with itself
						continue;

					itrCollision.second(receiver->second);								//calling the function and passing the next entity as a param

				}
				
			}
	}
	/*______________________________________________________*/
}