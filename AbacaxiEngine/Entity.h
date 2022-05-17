#pragma once



/*
	Entity.h
	Purpose: Base class for all entities. Entity is based on a component system called "Systems".
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/



#include "pch.h"
#include "Systems.h"
#include "EntityStates.h"



namespace abx {


	/*
		@brief Base class that will be inherited by all entity objects.
	*/
	class Entity {


		friend class EntityManager;		//"Befriending" manager so it has access to protected members.


	protected:


		std::vector<Ref<System>>		m_systems;		//Container that holds all entity's systems (components)
		std::vector<WeakRef<System>>	m_toRemove;		//Container hold pointers to systems that will soon be deleted from memory
		Ref<StateEntity>				m_state;		//Contains current entity state. Only one state per time.
		bool							m_stateLock;	//Locks in a specific state. Ideal when you don't want entity to switch state. e.g Dying state
		unsigned int					m_id;			//Unique identifier. It's set inside entity manager.


	public:



		/*
			@brief Base Constructor
		*/
		Entity() :
			m_systems	(),
			m_toRemove	(),
			m_state		(nullptr),
			m_stateLock	(false),
			m_id(0)
		{}




		/*
			@brief Virtual destructor.
		*/
		virtual ~Entity() {
			LogWarn("Entity has been destroyed");
		}




		/*
			@brief Will be called everytime an entity is created.
		*/
		virtual void OnCreate() {}




		/*
			@brief Will be called everytime an entity is destroyed.
		*/
		virtual void OnDestroy() {}




		/*
			@brief Updates entity's systems and states. Uses system time as seconds..
			@param const float& l_time
		*/
		void Update(const float& l_time) {
			
			for (auto& itr : m_systems)		//Updating all systems
				itr->Update(l_time);
			
			
			if (m_state)					//Updating current state
				m_state->Update(l_time);	
			
		}




		/*
			@brief Draw entity's systems.
		*/
		virtual void Render() {
			for (auto& itr : m_systems)
				itr->Render();
		}




		/*
			@brief Adds a system(component) to this entity.
			@return std::weak_ptr<T> to the newly created system
		*/
		template <class T>
		WeakRef<T> AddSystem();


	
		/*
			@brief Pushes a pointer of a system to be removed in late update.
			@see m_toRemove
		*/
		template<class T>
		void RemoveSystem();



		/*
			@brief Sets this entity's state. It creates an arbitrary entity state. Entity can only update one state.
			For example, the previous state will be deleted if this function is called with a different state as an parameter.
			If state is already in memory, it returns a weak pointer to that state.
			If isLocked boolean is true, switching state is impossible after this one.
			"Locked" is useful when entity only have to be in one state. 
			For example, if entity is dying, switch to a locked dying state so other states won't be pushed to entity.
			@param  const bool& isLocked (opitional)
			@return std::weak_ptr<T> to the newly created state
		*/
		template <class T>
		WeakRef<T> SetState();



		/*
			@brief Locks this entity's state. It creates an arbitrary entity state.
			"Locked" is useful when entity only have to be in one state.
			For example, if entity is dying, switch to a locked dying state so other states won't be pushed to entity.
			@param  const bool& isLocked (opitional)
			@return std::weak_ptr<T> to the newly created state
		*/
		template <class T>
		WeakRef<T> SetLockState();



		/*
			@brief Checks if entity is in templated state. If it is, it returns a valid weak pointer.
			If not, it returns an expired weak pointer.
			@return std::weak_ptr<T> state
		*/
		template<class T>
		std::weak_ptr<T> IsInState();



		/*
			@brief Performs system deletion if there's any in the removal queue.
			@see m_toRemove
		*/
		void LateUpdate() {
			while (m_toRemove.begin() != m_toRemove.end()) {

				for (auto itr = m_systems.begin(); itr != m_systems.end(); itr++) 

					if (typeid(**itr) == typeid(*m_toRemove.begin()->lock())) {


						/////////////////////////////////////////////////////////////////////
						//Debug
						abx::LogWarn( "[ENTITY] System removed from container: ["
							+ std::string(typeid(**itr).name()) + "]");
						/////////////////////////////////////////////////////////////////////


						m_systems.erase(itr);
						break;
					}

				m_toRemove.erase(m_toRemove.begin());

			}

		}




		/*
		@brief Gets a weak pointer to a system. Expired if not found.
		@returns std::weak_ptr<T> to a system
		*/
		template <class T>
		WeakRef<T> GetSystem();




		/*
			@brief Gets system according to its place in the container
			@param unsigned int index
			@return std::weak_ptr<System> system
		*/
		WeakRef<System> GetSystem(unsigned int l_index) {
			if (l_index < 0)
				return std::weak_ptr<System>();
			else if (l_index > m_systems.size())
				return std::weak_ptr<System>();
			return m_systems.at(l_index);
		}




		/*
			@brief Gets how many systems entity pocesses.
			@returns size
		*/
		unsigned int GetSystemCount() const { return m_systems.size(); }




		/*
		@brief Gets entity's ID.
		@returns const unsigned int& id.
		*/
		const unsigned int& GetId() const {
			return m_id; 
		}




	};




	/*
		@brief Definition. Adds a system(component) to this entity.
		@return std::weak_ptr<T> to the newly created system
	*/
	template<class T>
	inline WeakRef<T> Entity::AddSystem(){
		WeakRef<T> hasSystem = GetSystem<T>();		 //Checking if system is already in memory.
		if (!hasSystem.expired())
			return hasSystem.lock();

		//Code if not in memory

		Ref<T> newSystem = MakeRef<T>();
		newSystem->m_entity = this;					 //Binding entity's pointer to system.
		newSystem->OnCreate();
		m_systems.push_back(std::move(newSystem));   //Moving system and ownership to container
		return std::static_pointer_cast<T>(m_systems.back());
	}




	/*
		@brief Definition. Pushes a pointer of a system to be removed in late update.
		@see m_toRemove
	*/
	template<class T>
	inline void Entity::RemoveSystem(){
		for (auto& itr : m_systems) 
			if (typeid(*itr) == typeid(T)) {
				m_toRemove.push_back(itr);
				return;
			}
		

		LogError("[ENTITY] System could not be removed. Not found: [" +
			std::string(typeid(T).name()) + "]");
	}



	/*
		@brief Definition. Sets this entity's state. It creates an arbitrary entity state. Entity can only update one state.
		For example, the previous state will be deleted if this function is called with a different state as an parameter.
		If state is already in memory, it returns a weak pointer to that state.
		If isLocked boolean is true, switching state is impossible after this one.
		"Locked" is useful when entity only have to be in one state.
		For example, if entity is dying, switch to a locked dying state so other states won't be pushed to entity.
		@param  const bool& isLocked (opitional)
		@return std::weak_ptr<T> to the newly created state
	*/
	template<class T>
	inline WeakRef<T> Entity::SetState(){

		if (m_stateLock)									   //Not possible to switch states until it's false
			return WeakRef<T>();
		if (m_state)
			if (typeid(*m_state) == typeid(T))				   //If state is already being played
				return std::static_pointer_cast<T>(m_state);

		m_state = MakeRef<T>();
		m_state->BindEntity(this);							   //Binding state's owner
		return std::static_pointer_cast<T>(m_state);

	}



	/*
		@brief Locks this entity's state. It creates an arbitrary entity state.
		"Locked" is useful when entity only have to be in one state.
		For example, if entity is dying, switch to a locked dying state so other states won't be pushed to entity.
		@param  const bool& isLocked (opitional)
		@return std::weak_ptr<T> to the newly created state
	*/
	template<class T>
	inline WeakRef<T> Entity::SetLockState(){

		m_stateLock = true;									   //States called after this won't be able to change

		if (m_state)
			if (typeid(*m_state) == typeid(T))				   //If state is already being played
				return std::static_pointer_cast<T>(m_state);

		m_state = MakeRef<T>();
		m_state->BindEntity(this);							   //Binding state's owner
		return std::static_pointer_cast<T>(m_state);
	}

	/*
		@brief Definition. Checks if entity is in templated state. If it is, it returns a valid weak pointer.
		If not, it returns an expired weak pointer.
		@return std::weak_ptr<T> state
	*/
	template<class T>
	inline std::weak_ptr<T> Entity::IsInState(){
		if (typeid(*m_state) == typeid(T))
			return std::static_pointer_cast<T>(m_state);
		return std::weak_ptr<T>();
	}




	/*
		@brief Definition. Gets a weak pointer to a system. Expired if not found.
		@returns std::weak_ptr<T> to a system
	*/
	template<class T>
	inline WeakRef<T> Entity::GetSystem() {
		for (auto& itr : m_systems) 
			if (typeid(*itr) == typeid(T))
				return std::static_pointer_cast<T>(itr);
		
		return std::weak_ptr<T>();
	}


}