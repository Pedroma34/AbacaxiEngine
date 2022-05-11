#include "pch.h"
#include "EntitySquare.h"


namespace abx {

	EntitySquare::EntitySquare() {}
	EntitySquare::~EntitySquare(){}

	void EntitySquare::OnCreate(){
		//Rectangle system
		auto recSystem = AddSystem<SystemRectangleShape>().lock();
		
	}
}
