#pragma once


/*
	CommandInputs.h
	Purpose: Include all command inputs.
	@author Pedro Sergio de Castro Sarmento Filho
	15/May/2022
*/


/*Commands with entities*/
#include "CommandMoveRight.h"
#include "CommandMoveLeft.h"
#include "CommandMoveUp.h"
#include "CommandMoveDown.h"
#include "CommandAttack.h"+
#include "CommandKillEntity.h"

/*Commands using shared data*/
#include "CommandDestroyApplication.h"
#include "CommandDebug.h"
#include "CommandSelectEntity.h"

/*Commands using sf::Event::EventType*/
#include "CommandMouseMoved.h"