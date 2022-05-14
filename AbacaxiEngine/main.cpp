
/*
	main.cpp
	Purpose: Abacaxi Engine. 2D engine using SFML.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/



#include "pch.h"
#include "Application.h"



int main() {


	abx::Scope<abx::Application> app = abx::MakeScope<abx::Application>();		//Creating application


	while (!app->GetWindow()->GetDone()) {										//Main loop

		app->Update();
		app->Render();
		app->LateUpdate();

	}


	return 0;
}