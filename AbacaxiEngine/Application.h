#pragma once

/*
	Application.h
	Purpose: Manage and update the whole application as well as its members.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/


#include "pch.h"
#include "Window.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "Resources.h"


namespace abx {

	/*
		@brief Class that holds whole application and members.
	*/
	class Application {


		SharedData	  m_sharedData;
		Window		  m_window;		  //Window wrapper class of this application 
		Resources	  m_resources;	  //Resource manager using thor
		StateManager  m_stateMgr;	  //A manager that controls all machine states
		EntityManager m_entityMgr;	  //Manager that controls all entities and its components. Update and render functions are called inside machine states.
		sf::Time	  m_time;		  //Time 
		sf::Clock	  m_clock;	      //system clock


	public:


		/*
			@brief Constructor. Creates application and initialize its members.
		*/
		Application();


		/*
			@brief Destructor
		*/
		~Application();


		/*
			@brief Updates application members
		*/
		void Update();


		/*
			@brief Renders all application's drawables.
		*/
		void Render();


		/*
			@brief Perform late application's late updates. Commonly used for deleting memory.
		*/
		void LateUpdate();


		/*
			@brief Get a pointer to application's window object
			@return abx::Window* window
		*/
		Window* GetWindow();
	};
}