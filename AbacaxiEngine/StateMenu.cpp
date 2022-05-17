

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
		LogWarn(
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

		UpdateUi(l_time);

	}
	/*_________________________________________________________________________*/




	/*_________________________________________________________________________*/
	void StateMenu::Render() {

	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void StateMenu::UpdateUi(const float& l_time){

		const auto& winSize = SharedData::Window()->GetSize();

		/*Menu*/
		{
			bool b;
			ImGui::Begin("Menu", &b, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
			ImGui::SetWindowSize(ImVec2(winSize.x, winSize.y));
			ImGui::SetWindowPos(ImVec2(0, 0));
			ImGui::SetWindowFontScale(2);


			//Start
			ImGui::SetCursorPos(ImVec2(0, 0));
			if (ImGui::Button("Start", ImVec2(winSize.x * 0.50, winSize.y * 0.50))) {

				SharedData::StateMgr()->Remove   <StateMenu>();
				SharedData::StateMgr()->SwitchTo <StateGame>();

			}

			//Quit
			ImGui::SetCursorPos(ImVec2(winSize.x / 2, winSize.y / 2));
			if (ImGui::Button("Quit", ImVec2(winSize.x * 0.50, winSize.y * 0.50)))
				SharedData::Window()->DestroyApplication();


			ImGui::End();
		}

	}
	/*_________________________________________________________________________*/
}
