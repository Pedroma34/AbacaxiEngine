

/*
	StateGame.cpp
	Purpose: Game machine state that will update and render game's logic.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"
#include "StateMenu.h"
#include "StateManager.h"
#include "Window.h"

namespace abx {




	/*_________________________________________________________________________*/
	StateMenu::StateMenu() {}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	StateMenu::~StateMenu() {
		//Debugging
		LogWarn(m_sharedData,
			"[STATE] Machine state destroyed: [" +
			std::string(typeid(*this).name()) + "]"
		);
	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::OnCreate() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::OnDestroy() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::Activate() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::Deactivate() {

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::Update(const float& l_time) {

		m_sharedData->m_stateMgr->Remove<StateMenu>();
		m_sharedData->m_stateMgr->SwitchTo<StateGame>();

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::Render() {

	}
	/*_________________________________________________________________________*/
}