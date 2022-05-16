#pragma once



/*
	Window.h
	Purpose: Create a SFML window and handle its events.
	@author Pedro Sergio de Castro Sarmento Filho
	10/May/2022
*/



#include "pch.h"



namespace abx {



	/*
		Wrapper class for an SFML window
	*/
	class Window {


		sf::RenderWindow m_window;		  //SFML window
		std::string		 m_title;		  //Title of the window
		sf::Vector2u	 m_size;		  //Size of the window
		bool			 m_vSync;		  //Vertical sync
		bool			 m_fullScreen;	  //Is the application fullscreen?
		bool			 m_isDone;		  //Is the application done?
		bool			 m_isFocused;	  //Is window on focus?

	public:


		/*
			@brief Constructor. Creates a window.
			@param &string Title of the window
			@param &sf::Vector2u Size of the window
			@param SharedData* Pointer to application's shared data
		*/
		Window(const std::string& l_title, const sf::Vector2u& l_size);



		/*
			@brief Destructor
		*/
		~Window();



		/*
			@brief Updates SFML events.
			@param &sf::Time Application's time member.
		*/
		void Update(const sf::Time& l_time);



		/*
			@brief Clears SFML window.
		*/
		void Clear();



		/*
			@brief Draws a drawable object to the window.
			@param *sf::Drawable An SFML Drawable object
		*/
		void Draw(const sf::Drawable* l_drawable);



		/*
			@brief Display changes made to the window.
		*/
		void Display();



		/*
			@brief Switch fullscreen boolean, close the window, and create it again with the new boolean state.
			@param const bool& Boolean to fullscreen
		*/
		void SetFullScreen(const bool& l_fullScreen);



		/*
			@brief Switch isDone boolean and consequently destroys application.
		*/
		void DestroyApplication();

		

		/*
			@brief Get the size of the window
			@return sf::Vector2u& Size of the window
		*/
		const sf::Vector2u& GetSize() const;



		/*
			@brief Get vSync boolean
			@return	const bool& vSync
		*/
		const bool& GetvSync() const;



		/*
			@brief Get full screen boolean
			@return const bool& vSync
		*/
		const bool& GetFullScreen() const;



		/*
			@brief Get if window is done boolean
			@return const bool& isDone
		*/
		const bool& GetDone() const;



		/*
			@brief Get if window is focused
			@return const bool& focus
		*/
		const bool& GetFocus() const;



		/*
			@brief Get a pointer the window
			@return sf::Window* window
		*/
		sf::Window* GetWindow();



	private:



		/*
			@brief Creates an SFML window.
		*/
		void Create();



	};

}