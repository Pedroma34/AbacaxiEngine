#pragma once
#include "Entity.h"

namespace abx {

	class EntitySquare : public Entity {


	public:
		EntitySquare();
		~EntitySquare();

		void OnCreate() override;

	};


}