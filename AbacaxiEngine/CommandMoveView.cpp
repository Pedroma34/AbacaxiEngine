



/*
	CommandMoveView.cpp
	Purpose: Command callback that moves window view
	It is invoked through the event manager.
	@author Pedro Sergio de Castro Sarmento Filho
	21/May/2022
*/




#include "pch.h"
#include "CommandMoveView.h"




namespace abx {




	/*________________________________*/
	void CommandMoveView::Execute(sf::Event l_event){

		if (!SharedData::Debug())
			return;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

			float speed = SharedData::View().getSize().x / 2 * 0.5 * SharedData::Time()->asSeconds();
			const auto& oldMousePos = Debug::GetLastMousePos();
			auto offset = sf::Vector2f(
				oldMousePos.x - l_event.mouseMove.x,
				oldMousePos.y - l_event.mouseMove.y
			);

			SharedData::View().move(offset.x * speed, offset.y * speed);
		}

		Debug::SetLastMousePos(sf::Vector2f(l_event.mouseMove.x, l_event.mouseMove.y));

	}
	/*________________________________*/




}