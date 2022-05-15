#pragma once



/*
	Command.h
	Purpose: Base class for all commands. Command patter is useful to execute callbacks whenever is necessary
	with the power of execute and undo commands.
	@author Pedro Sergio de Castro Sarmento Filho
	14/May/2022
*/



#include "pch.h"



namespace abx {



	/*
		@brief Base class for all commands. Used for the command pattern.
	*/
	class Command {
	public:



		/*
			@brief Virtual destructor
		*/
		virtual ~Command() {}



		/*
			@brief Executes a command
		*/
		virtual void Execute() {}



		/*
			@brief Executes a command with an entity
		*/
		virtual void Execute(WeakRef<class Entity> l_entity) {}



		/*
			@brief Undoes a command
		*/
		virtual void Undo() {}



		/*
			@brief Undoes a command with an entity
		*/
		virtual void Undo(std::weak_ptr<Entity> l_entity) {}



	};

}