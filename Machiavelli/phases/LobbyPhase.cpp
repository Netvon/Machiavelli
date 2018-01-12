#include "LobbyPhase.h"
#include "GamePhase.h"

namespace machiavelli
{
	LobbyPhase::LobbyPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		enable_defaults();
	}

	LobbyPhase::~LobbyPhase()
	{

	}

	void LobbyPhase::print(const Socket & socket, const Player & player)
	{
	}

	void LobbyPhase::entered_phase(const Socket & socket, const Player & player)
	{
		amount_in_game++;

		if (amount_in_game >= 2) {

			//state()->broadcast("Okay, that's two players! Let's begin.\r\n");
			state()->add_phase<machiavelli::GamePhase>("game");
			state()->navigate_to("game");

			amount_in_game = 0;
		}
		else {
			socket << "There's not enough players yet.\n\r";
		}
	}

	void LobbyPhase::add_options()
	{
	}
}
