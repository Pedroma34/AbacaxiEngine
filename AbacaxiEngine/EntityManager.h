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


		std::vector<std::pair<unsigned int,Ref<Entity>>>					m_entities;			//Container holds all the entities in the application. First is ID and second is the entity.
		std::vector<std::pair<unsigned int, Ref<Entity>>>				    m_toAdd;			//Queue to be added in late update.
		std::map<WeakRef<Entity>, std::function<void(WeakRef<Entity>)>>		m_collisionQueue;	//Collision queue.
		std::vector<unsigned int>											m_toRemove;			//Removal queue
		unsigned int														m_id;				//Unique id that will be passed onto entities on creation
		SharedData*															m_sharedData;		//Pointer to application's shared data
	

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
			@brief Adds an entity to the container. It uses the object class as an templated sort of parameter
			that will create an entity from that object. For example: Add<Zombie>(); The class "Zombie" should
			inherit from entity.
			@return A weak pointer to the newly added entity.
		*/
		template<class T>
		WeakRef<T> Add();



		/*
			@brief Adds a pure entity to the container. This function enables 
			creating entities on the fly without the need for creating a class for that entity.
			Note that systems(components) needs to be added, since this entity is just an empty entity.
			It is optimal to use the templated version of this function, which needs an abstract class as a template.
			[IMPORTANT] = l_entity POINTER WILL BE EMPTY. USE RETURNED POINTER TO MODIFY ENTITY
			@param std::shared_ptr<Entity>& entity
			@return A weak pointer to the newly added entity.
		*/
		WeakRef<Entity> Add(Ref<Entity> &l_entity);



		/*
			@brief Adds a pure entity to the container at a late update (end of program's tick). This function enables
			creating entities on the fly without the need for creating a class for that entity.
			Note that systems(components) needs to be added, since this entity is just an empty entity.
			It is optimal to use the templated version of this function, which needs an abstract class as a template.
			[IMPORTANT] = l_entity POINTER WILL BE EMPTY. USE RETURNED POINTER TO MODIFY ENTITY
			@param std::shared_ptr<Entity>& entity
			@return A weak pointer to the newly added entity.
		*/
		WeakRef<Entity> AddLate(Ref<Entity>& l_entity);



		/*
			@brief Adds an entity to the container at a late update (end of program's tick).
			Useful when adding entities inside update function.
			It uses the object class as an templated sort of parameter
			that will create an entity from that object.
			For example: AddLate<Zombie>(); The class "Zombie" should inherit from entity.
			@return A weak pointer to entity in queue.
			@see m_toAdd
		*/
		template<class T>
		std::weak_ptr<T> AddLate();



		/*
			@brief Adds collision to the queue. It takes a weak pointer to an entity, which is the caller,
			a pointer to the function we want to bind, and a pointer to the object that owns that function.
			That bound function will be called inside CollisionCheck function.
			Furthermore, said bound function must have a weak pointer to a entity, which will be the receiver.
			@param std::weak_ptr<Entity> entity
			@param void(T::*function)(std::weak_ptr<Entity>) function
			@param T* owner
		*/
		template<class T>
		bool AddCollisionQueue(WeakRef<Entity> l_entity, void(T::* l_func)(WeakRef<Entity>), T* l_instance);



		/*
			@brief Adds an entity to the removal queue. Takes an entity id.
			@param const unsigned int id
			@see m_toRemove
		*/
		void Remove(const unsigned int& l_toRemove);



		/*
			@brief Removes all entities as well as add, removal, and collision queues.
			Do not call this inside this manager's update functions.
		*/
		void RemoveAll();



		/*
			@brief Performs entity and systems removal. Also adds entities in queue.
		*/
		void LateUpdate();



		/*
			@brief Remove all entities, collisions, add, and remove queues.
			@see m_toRemove
		*/
		void PurgeEntities();



		/*
			@brief Returns a weak pointer to an entity. Uses unique id as an parameter.
			@param const unsigned int& id
		*/
		WeakRef<Entity> Get(const unsigned int& l_id);



		/*
			@brief Returns how many entities are in memory.
			@returns unsigned int entityCount
		*/
		unsigned int GetSize();



	private:



		/*
			@brief Moves an entity into main container.
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
			It loops through all entities, "caller", and checks if that entity has a function in the collision queue.
			If so, it then iterates once more through all entities, "receiver",
			and calls our "caller" function with a weak pointer to the receiver. 
			Consequently, the function performs any logic with access to the receiver.
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
		Ref<T> newEntity		 = MakeRef<T>();
		newEntity->m_sharedData  = m_sharedData;				//Binding shared data
		newEntity->m_id			 = m_id;						//Binding ID
		newEntity->OnCreate();
		m_toAdd.emplace_back(m_id, std::move(newEntity));		//Moving entity add queue
		m_id++;

		//Debug
		LogInfo(m_sharedData, "[ENTITY] New entity into add queue: " + std::string(typeid(T).name()));


		return std::static_pointer_cast<T>(m_toAdd.back().second);
	}




	/*
		Definition. Adds collision to the queue. It takes a weak pointer to an entity, which is the caller,
		a pointer to the function we want to bind, and a pointer to the object that owns that function.
		That bound function will be called inside CollisionCheck function.
		Furthermore, said bound function must have a weak pointer to a entity, which will be the receiver.
		@param std::weak_ptr<Entity> entity
		@param void(T::*function)(std::weak_ptr<Entity>) function
		@param T* owner
	*/
	template<class T>
	inline bool EntityManager::AddCollisionQueue(WeakRef<Entity> l_entity, void(T::* l_func)(WeakRef<Entity>), T* l_instance){
		auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
		return m_collisionQueue.emplace(l_entity, temp).second;
	}


}