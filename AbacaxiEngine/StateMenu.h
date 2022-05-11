#pragma once


/*
	StateMenu.h
	Purpose: Menu machine state that will update and render menu's logic.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"
#include "State.h"

namespace abx {

	/*
		@brief Menu class that updates and renders menu's logic.
		Inherited from State.
	*/
	class StateMenu : public State {



	public:



		/*
			@brief Base Constructor
		*/
		StateMenu();



		/*
			@brief Virtual destructor.
		*/
		~StateMenu();



		/*
			@brief Will be called when this state is created.
		*/
		void OnCreate() override;



		/*
			@brief Will be called when this state is destroyed.
		*/
		void OnDestroy() override;



		/*
			@brief Will be called when this state is activated.
		*/
		void Activate() override;



		/*
			@brief Will be called when this state is deactivated.
		*/
		void Deactivate() override;



		/*
			@brief Updates this state. Uses system time as seconds..
			@param const float& l_time
		*/
		void Update(const float& l_time) override;



		/*
			@brief Renders this state.
		*/
		void Render() override;
	};
}