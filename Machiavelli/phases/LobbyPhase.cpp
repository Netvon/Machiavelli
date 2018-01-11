#include "LobbyPhase.h"

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

	}

	void LobbyPhase::add_options()
	{
	}
}
