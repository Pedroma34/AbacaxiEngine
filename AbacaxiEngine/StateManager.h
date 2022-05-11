#pragma once


/*
	StateManager.h
	Purpose: Manage, update, and render all machine states, including transparency, transcendency, and memory.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/



#include "pch.h"
#include "MachineStates.h" //All states


namespace abx {



	/*
		@brief Class will manage, update, and render all machine states, including transparency, transcendency, and memory allocation.
	*/
	class StateManager {


		SharedData* m_sharedData;					//Pointer to application's shared datas
		std::vector<Ref<State>> m_states;			//Container that holds all states. Ref should be passed only with weak_ptr
		std::vector<WeakRef<State>> m_toRemove;		//Container hold pointers to states that will soon be deleted from memory


	public:



		/*
			@brief Constructor
			@param SharedData* Pointer to application's shared data
		*/
		StateManager(SharedData* l_sharedData);



		/*
			@brief Destructor
		*/
		~StateManager();



		/*
			@brief Updates all states in container. Also manage transcendency
			@param const float& Reference to application's time in seconds
		*/
		void Update(const float& l_time);



		/*
			@brief Renders all states in container. Also manages transparency
		*/
		void Render();



		/*
			@brief Performs state removal from container at the end of the application cycle.
			@see m_toRemove
		*/
		void LateUpdate();



		/*
			@brief Push a state to the back of container. If state is not in container, it creates a new one.
		*/
		template<class T>
		void SwitchTo();



		/*
			@brief Push a state pointer to a container used to delete states during late update.
			@see m_toRemove
		*/
		template <class T>
		void Remove();



		/*
			@brief Returns a weak pointer to a state. Returns expired if not in container.
			@returns std::weak_ptr to a state
		*/
		template <class T>
		WeakRef<T> GetState();


	private:



		/*
			@brief Creates and returns a weak pointer to a state. Function is only called in SwitchTo funtion.
			@returns std::weak_ptr to a newly created state
		*/
		template<class T>
		WeakRef<T> Create();
	};



	/*
			@brief Definition. Push a state to the back of container. If state is not in container, it creates a new one.
	*/
	template<class T>
	inline void StateManager::SwitchTo(){
		for(auto itr = m_states.begin(); itr != m_states.end(); itr++)
			if (typeid(*itr) == typeid(T)) {			   //If already in memory
				m_states.back()->Deactivate();			   //Deactivating current state since we're pushing one to the back
				Ref<State> tmpState = std::move(*itr);     //Passing ownership to a temporary state ref because we're deleting it from container
				m_states.erase(itr);					   //Deleting from stack, but it's store in the temporary variable
				tmpState->Activate();
				m_states.push_back(std::move(tmpState));   //Pushing and passing ownership to the container.
				//Debug
				LogInfo(m_sharedData, "[STATE] State in memory, switching to: [" + std::string(typeid(T).name()) + "]");

				return;
			}

		//Executing code if state is not in container

		if (!m_states.empty())
			m_states.back()->Deactivate();		//Checking if there's a state in the back of container and deactivating it

		Ref<T> newState = Create<T>().lock();   //Creating new state
		newState->Activate();
	}




	/*
			@brief Definition. Push a state pointer to a container used to delete states during late update.
			@see m_toRemove
	*/
	template<class T>
	inline void StateManager::Remove(){
		for(auto& itr : m_states)
			if (typeid(*itr) == typeid(T)) {
				m_toRemove.push_back(itr);		//Pusing weak pointer to container. @see m_toRemove
			}
	}




	/*
			@brief Definition. Returns a weak pointer to a state. Returns expired if not in container.
			@returns std::weak_ptr to a state
		*/
	template<class T>
	inline WeakRef<T> StateManager::GetState(){
		for (auto& itr : m_states) 
			if (typeid(*itr) == typeid(T))
				return std::static_pointer_cast<T>(itr);
		
		return WeakRef<T>();								 //nullptr
	}




	/*
			@brief Definition. Creates and returns a weak pointer to a state. Function is only called in SwitchTo funtion.
			@returns std::weak_ptr to a newly created state
		*/
	template<class T>
	inline WeakRef<T> StateManager::Create(){
		Ref<State> newState = MakeRef<T>();
		newState->m_sharedData = m_sharedData;					//Binding shared data
		newState->OnCreate();
		m_states.push_back(std::move(newState));				//Moving state and ownership to the container

		//Debug
		abx::LogInfo(m_sharedData, "[STATE] State created and pushed to container: [" + std::string(typeid(*m_states.back()).name()) + "]");
		abx::LogInfo(m_sharedData, "[STATE] State container size: [" + std::string(std::to_string(m_states.size())) + "]");

		return std::static_pointer_cast<T>(m_states.back());
	}


}