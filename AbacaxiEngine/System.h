#pragma once


/*
	System.h
	Purpose: Base class for all systems (components). Systems act as an entity component system.
	@author Pedro Sergio de Castro Sarmento Filho
	11/May/2022
*/


#include "pch.h"


namespace abx {



	/*
		@brief Base class that will be inherited by all systems used by entities, 
		acting as an entity component system. All its functions are optinial. For example,
		if a system only holds a floating point, it doesn't need to be updated nor rendered.
	*/
	class System {

		friend class Entity;		//Befriending all entities so they can use protected members.


	protected:


		class Entity* m_entity;		//Pointer to the owner if this system. Foward declaration. Must be bound during creation.


	public:



		/*
			@brief Base Constructor
		*/
		System() :
			m_entity(nullptr)
		{}



		/*
			@brief Virtual destructor.
		*/
		virtual ~System() {}



		/*
			@brief Updates system logic.
			Not necessery if system doesn't need to be updated (if it only holds data).
			@param const float& time
		*/
		virtual void Update(const float& l_time) {}




		/*
			@brief Render system drawables. 
			Not necessery if system doesn't need to be drawn (if it only holds data).
		*/
		virtual void Render() {}




		/*
			@brief Will be called when state is created.
			Not necessery if system's members don't need to be initialized.
		*/
		virtual void OnCreate() {}


	};



}