#include "PlayPhase.h"
using namespace std::placeholders;

namespace machiavelli
{
	PlayPhase::PlayPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
	}

	PlayPhase::~PlayPhase()
	{
	}

	void PlayPhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void PlayPhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the PlayPhase!\r\n";

		//nextTurn(socket, player);
	}

	void PlayPhase::add_options()
	{
		auto& game = state()->game();
		auto& currentPlayer = game.current_player()->get_player();

		if (currentPlayer == game.getKing()) {
			add_option("0", "Roep volgende karakter op", std::bind(&PlayPhase::handle_turn, this, _1, _2), true);
		}
	}

	void PlayPhase::handle_turn(const Socket & socket, Player & player)
	{
		
	}

	void PlayPhase::nextTurn(const Socket & socket, const Player & player)
	{
		
	}
}