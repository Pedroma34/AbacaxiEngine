

/*
	Window.cpp
	Purpose: Create a SFML window and handle its events.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/



#include "pch.h"
#include "Window.h"
#include "EventManager.h"

namespace abx {


	/*_________________________________________________________________________*/
	Window::Window(const std::string& l_title, const sf::Vector2u& l_size)	:
		m_window (),
		m_title(l_title),
		m_size(l_size),
		m_vSync(true),
		m_fullScreen(false),
		m_isDone(false),
		m_isFocused(true)
	{
		SharedData::SetWindow(this);
		Create();							//Creating window
		ImGui::SFML::Init(m_window);		//Initializing Imgui
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	Window::~Window(){}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::Update(const sf::Time& l_time)	{

		m_size = m_window.getSize();							//Copying window size into a member
		sf::Event evnt;
		while (m_window.pollEvent(evnt)) {

			if (evnt.type == sf::Event::LostFocus) {
				LogWarn("[WINDOW] Not focused");
				m_isFocused = false;
			}
			else if (evnt.type == sf::Event::GainedFocus) {
				LogWarn("[WINDOW] Focused");
				m_isFocused = true;
			}
			else if (evnt.type == sf::Event::Closed)
				m_isDone = true;								//Terminate application

			if (m_isFocused)
				SharedData::EventMgr()->HandleEvent(&evnt);	    //Update command callbacks

			ImGui::SFML::ProcessEvent(m_window, evnt);
		}

		if (m_isFocused)
			SharedData::EventMgr()->HandleInput();			    //Update real time user input

		ImGui::SFML::Update(m_window, l_time);

	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::Clear(){
		m_window.clear(sf::Color::Black);
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::Draw(const sf::Drawable* l_drawable){
		m_window.draw(*l_drawable);
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::Display(){
		m_window.display();
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::RenderImgui(){
		ImGui::SFML::Render(m_window);
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::SetFullScreen(const bool& l_fullScreen){
		m_fullScreen = l_fullScreen;

		m_window.close();

		Create();
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::DestroyApplication(){
		m_isDone = true;
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/

	const sf::Vector2u& Window::GetSize() const{
		return m_size;
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	const bool& Window::GetvSync() const{
		return m_vSync;
	}



	/*_________________________________________________________________________*/
	const bool& Window::GetFullScreen() const{
		return m_fullScreen;
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	const bool& Window::GetDone() const{
		return m_isDone;
	}



	/*_________________________________________________________________________*/
	const bool& Window::GetFocus() const{
		return m_isFocused;
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	sf::RenderWindow* Window::GetWindow(){
		return &m_window;
	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	sf::FloatRect Window::GetViewSpace(){

		auto viewCenter    =  m_window.getView().getCenter();
		auto viewSize	   =  m_window.getView().getSize();
		auto viewSizeHalf  =  sf::Vector2f(
			viewSize.x / 2, 
			viewSize.y / 2
		);

		sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);

		return viewSpace;

	}
	/*_________________________________________________________________________*/



	/*_________________________________________________________________________*/
	void Window::Create(){
		auto style = m_fullScreen ? sf::Style::Fullscreen : sf::Style::Close;

		m_window.create(sf::VideoMode(m_size.x, m_size.y, 32), m_title, style);

		if (m_vSync)
			m_window.setVerticalSyncEnabled(true);
		else
			m_window.setVerticalSyncEnabled(false);

		//Degubbing
		LogInfo( 
			"[WINDOW] SFML window created : {" + 
			std::string(std::to_string(m_size.x) + "} {" +
			std::to_string(m_size.y) + "} vSync{" +
			std::to_string(m_vSync) + "}"
			));
	}
	/*_________________________________________________________________________*/
}
