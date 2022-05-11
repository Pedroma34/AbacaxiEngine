#pragma once
#include "System.h"


namespace abx {

	class SystemRectangleShape : public System {
		sf::RectangleShape m_shape;

	public:

		SystemRectangleShape();
		~SystemRectangleShape();

		void Render()   override;
		void OnCreate() override;


		sf::RectangleShape* GetShape();
	};

}