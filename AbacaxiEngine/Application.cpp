


/*
	Application.cpp
	Purpose: Manage and update the whole application as well as its members.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/



#include "pch.h"
#include "Application.h"
#include "CommandInputs.h"



namespace abx {


	/*_________________________________________________________________________*/
	Application::Application() :
		m_window("Abacaxi", sf::Vector2u(1280,720))   ,
		m_resources()								  ,
		m_stateMgr									(),
		m_entityMgr									(),
		m_eventMgr									(),
		m_time										(),
		m_clock										()

	{

		srand(time(NULL));

		//Initializing share data//
		SharedData::SetTime(&m_time);
		SharedData::SetDebug(true);
		////////////////////////////////////////////////////////////////////////////////////

		//Intializing machine state
		m_stateMgr.SwitchTo<StateMenu>();														//Starting domino effect
		////////////////////////////////////////////////////////////////////////////////////

		//Binding global commands
		SharedData::EventMgr()->Bind<CommandMoveView>(sf::Event::MouseMoved);		//Updating last mouse position
		////////////////////////////////////////////////////////////////////////////////////
	}



	/*_________________________________________________________________________*/
	Application::~Application()	{}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Application::Update(){

		m_window.Update(m_time);

		if (m_window.GetFocus())
			m_stateMgr.Update(m_time.asSeconds());

	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Application::Render(){
		m_window.Clear();
		m_stateMgr.Render();
		m_window.RenderImgui();
		m_window.Display();
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Application::LateUpdate(){
		m_time = m_clock.restart();
		m_stateMgr.LateUpdate();
		m_entityMgr.LateUpdate();
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	Window* Application::GetWindow(){
		return &m_window;
	}
	/*_________________________________________________________________________*/
}
