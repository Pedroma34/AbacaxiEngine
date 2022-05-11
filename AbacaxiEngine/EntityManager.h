#pragma once



/*
	EntityManager.h
	Purpose: Manage, update, and render all entities, including systems (components) and states.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/




#include "pch.h"
#include "Entities.h"



namespace abx {


	/*
		@brief Class will manage, update, and render all machine states, including transparency, transcendency, and memory allocation.
	*/
	class EntityManager {


		std::vector<std::pair<unsigned int,Ref<Entity>>>    m_entities;			//Container holds all the entities in the application. First is ID and second is the entity.
		std::vector<std::pair<unsigned int, Ref<Entity>>>	m_toAdd;			//Queue to be added in late update.
		std::map<Entity*, std::function<void(Entity*)>>		m_collisionQueue;	//Collision queue.
		std::vector<unsigned int>						    m_toRemove;			//Removal queue
		unsigned int										m_id;				//Unique id that will be passed onto entities on creation
		SharedData*											m_sharedData;		//Pointer to application's shared data
	

	public:



		/*
			@brief Constructor
			@param SharedData* Pointer to application's shared data
		*/
		EntityManager(SharedData* l_sharedData);



		/*
			@brief Destructor
		*/
		~EntityManager();




		/*
			@brief Updates all entities in container and its systems and states.
			@param const float& Reference to application's time in seconds
		*/
		void Update(const float& l_time);



		/*
			@brief Renders all entities in container if needed.
		*/
		void Render();



		/*
			@brief Adds an entity to the container.
			@return A weak pointer to the newly added entity.
		*/
		template<class T>
		WeakRef<T> Add();



		/*
			@brief Adds an entity to the container at a late update (end of program's tick).
			@return A weak pointer to entity in queue.
			@see m_toAdd
		*/
		template<class T>
		std::weak_ptr<T> AddLate();



		/*
			@brief Adds an entity to the removal queue. Takes an entity id.
			@param const unsigned int id
			@see m_toRemove
		*/
		void Remove(const unsigned int& l_toRemove);



		/*
			@brief Performs entity and systems removal. Also adds entities in queue.
		*/
		void LateUpdate();



		/*
			@brief Remove all entities, collisions, add, and remove queues.
			@see m_toRemove
		*/
		void PurgeEntities();



	private:



		/*
			@brief Moves an entity into container.
			@param std::shared_ptr<Entity>& entity
		*/
		void CopyEntity(Ref<Entity>& l_entity);



		/*
			@brief Deletes an entity from container using its id.
			@param const unsigned int& id
		*/
		void Delete(const unsigned int& l_id);



		/*
			@brief Performs collision check if any in queue.
		*/
		void CollisionCheck(const float& l_time);
	};



	/*
		@brief Definition. Adds an entity to the container.
		@return A weak pointer to the newly added entity.
	*/
	template<class T>
	inline WeakRef<T> EntityManager::Add(){
		Ref<T> newEntity = MakeRef<T>();
		newEntity->m_sharedData = m_sharedData;					//Binding shared data
		newEntity->m_id = m_id;									//Binding ID
		newEntity->OnCreate();
		m_entities.emplace_back(m_id, std::move(newEntity));	//Moving entity to container
		m_id++;													//Increasing id count so next entity will have unique id

		//Debug
		LogInfo(m_sharedData, "[ENTITY] New entity added: " + std::string(typeid(T).name()));

		return std::static_pointer_cast<T>(m_entities.back().second);
	}



	/*
		@brief Adds an entity to the container at a late update (end of program's tick).
		@return A weak pointer to the newly added entity.
	*/
	template<class T>
	inline std::weak_ptr<T> EntityManager::AddLate(){
		Ref<T> newEntity = MakeRef<T>();
		newEntity->m_sharedData = m_sharedData;					//Binding shared data
		newEntity->m_id = m_id;									//Binding ID
		newEntity->OnCreate();
		m_toAdd.emplace_back(m_id, std::move(newEntity));		//Moving entity add queue
		m_id++;

		//Debug
		LogInfo(m_sharedData, "[ENTITY] New entity into add queue: " + std::string(typeid(T).name()));


		return std::static_pointer_cast<T>(m_toAdd.back().second);
	}


}