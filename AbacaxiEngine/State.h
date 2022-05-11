#pragma once

/*
	State.h
	Purpose: Base class for all machine states.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"

namespace abx {


	/*
		@brief Base class that will be inherited by all machine state objects.
	*/
	class State {


		friend class StateManager;   //Foward declaration and "befriending" manager so it has access to protected members.


	protected:

		bool m_transparent;			 //Defines if state will be updated along with other states.
		bool m_transcendent;		 //Defines if state will be drawn along with other states.
		SharedData* m_sharedData;	 //Pointer to all shared data. Must be bound when state is created.



	public:
		


		/*
			@brief Base Constructor
		*/
		State() : 
			m_transcendent(false),
			m_transparent(false), 
			m_sharedData(nullptr) 
		{}



		/*
			@brief Virtual destructor.
		*/
		virtual ~State() {}



		/*
			@brief Will be called everytime a machine state is created.
		*/
		virtual void OnCreate() = 0;



		/*
			@brief Will be called everytime a machine state is destroyed.
		*/
		virtual void OnDestroy() = 0;



		/*
			@brief Will be called everytime a machine state is activated. Right after is created.
		*/
		virtual void Activate() = 0;



		/*
			@brief Will be called everytime a machine state is deactivated. Right after it's destroyed.
		*/
		virtual void Deactivate() = 0;



		/*
			@brief Updates machine state. Uses system time as seconds..
			@param const float& l_time
		*/
		virtual void Update(const float& l_time) = 0;



		/*
			@brief Renders machine state's drawables.
		*/
		virtual void Render() = 0;




		/*
			@brief Set machine state's transparency. Dictates if state will be updated with other states.
		*/
		void SetTransparency(const bool& l_transparency) { m_transparent = l_transparency; }



		/*
			@brief Set machine state's transcendency. Dictates if state will be drawn with other states.
		*/
		void SetTranscendency(const bool& l_transcendency) { m_transcendent = l_transcendency; }



		/*
			@brief Gets if state is transparent.
			@returns const bool& transparent.
		*/
		const bool& isTransparent() const { return m_transparent; }



		/*
		@brief Gets if state is transcendent.
		@returns const bool& transcendent.
		*/
		const bool& isTranscendent() const { return m_transcendent; }
	};

}