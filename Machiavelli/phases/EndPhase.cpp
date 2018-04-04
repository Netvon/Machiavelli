#include "EndPhase.h"

namespace machiavelli
{
	EndPhase::EndPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
	}

	EndPhase::~EndPhase()
	{
	}

	void EndPhase::add_options()
	{
	}

	void EndPhase::entered_phase(const Socket & socket, const Player & player)
	{
		print_info(socket, player);

	}

	void EndPhase::countPoints()
	{
		auto& game = state()->game();

		auto player1Score = game.getPlayers().at(0)->get_player().score();
		auto player2Score = game.getPlayers().at(1)->get_player().score();

		std::ostringstream scores;

		scores << "Scores;\r\n";
		scores << "- " << game.getPlayers().at(0)->get_player().name() << ": " << player1Score << "\r\n";
		scores << "- " << game.getPlayers().at(1)->get_player().name() << ": " << player2Score << "\r\n";

		game.broadcast(scores.str());

		if (player1Score > player2Score) {
			game.broadcast(game.getPlayers().at(0)->get_player().name() + " is the winner!");
		}
		else {
			game.broadcast(game.getPlayers().at(1)->get_player().name() + " is the winner!");
		}
	}

	void EndPhase::handle_turn(const Socket & socket, const Player & player)
	{
	}

	void EndPhase::print(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the EndPhase!\r\n";

		reset_options(true);
	}

	void EndPhase::nextTurn(const Socket & socket, const Player & player)
	{
	}
}