

/*
	StateManager.cpp
	Purpose: Manage, update, and render all machine states, including transparency, transcendency, and memory.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"
#include "StateManager.h"

namespace abx {


	/*_____________________________________________________*/
	StateManager::StateManager() :
		m_states(),
		m_toRemove()
	{
		SharedData::SetStateMgr(this);
	}
	/*_____________________________________________________*/




	/*_____________________________________________________*/
	StateManager::~StateManager()
	{
	}
	/*_____________________________________________________*/




	/*_____________________________________________________*/
	void StateManager::Update(const float& l_time){
		if (m_states.empty())
			return;

		if (m_states.back()->isTranscendent() && m_states.size() > 1) {		//If current state is transcendent, we will update the one behind it

			auto itr = m_states.end();
			while (itr != m_states.begin()) {
				if (itr != m_states.end()) {
					if (!itr->get()->isTranscendent()) {
						break;
					}
				}
				--itr;
			}
			for (; itr != m_states.end(); ++itr) {
				itr->get()->Update(l_time);
			}
		}

		else																//If current state is not transcendent, just update it
			m_states.back()->Update(l_time);
	}
	/*_____________________________________________________*/




	/*_____________________________________________________*/
	void StateManager::Render(){
		if (m_states.empty())
			return;

		if (m_states.back()->isTransparent() && m_states.size() > 1) {		//If current state is transparent, we will draw the one behind it

			auto itr = m_states.end();
			while (itr != m_states.begin()) {
				if (itr != m_states.end()) {
					if (!itr->get()->isTransparent()) {
						break;
					}
				}
				--itr;
			}
			for (; itr != m_states.end(); ++itr) {
				itr->get()->Render();
			}
		}
		else																//If current state is not transparent, just draw it
			m_states.back()->Render();
	}
	/*_____________________________________________________*/




	/*_____________________________________________________*/
	void StateManager::LateUpdate(){
		while (m_toRemove.begin() != m_toRemove.end()) {

			for (auto itr = m_states.begin(); itr != m_states.end(); itr++) {

				if (typeid(**itr) == typeid(*m_toRemove.begin()->lock())) {
					itr->get()->OnDestroy();

					/////////////////////////////////////////////////////////////////////
					//Debug
					abx::LogWarn( "[STATE] State removed from container: [" 
						+ std::string(typeid(**itr).name()) + "]");
					/////////////////////////////////////////////////////////////////////


					m_states.erase(itr);


					/////////////////////////////////////////////////////////////////////
					//Debug
					abx::LogInfo( "[STATE] State container size: [" + 
						std::string(std::to_string(m_states.size())) + "]");
					/////////////////////////////////////////////////////////////////////


					break;
				}
			}

			m_toRemove.erase(m_toRemove.begin());
		}
	}
	/*_____________________________________________________*/




}
