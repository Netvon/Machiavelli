#include "EndPhase.h"

namespace machiavelli
{
	EndPhase::EndPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
	}

	void EndPhase::add_options()
	{
	}

	void EndPhase::reset()
	{
		player1Score = -1;
		player2Score = -1;
		in_phase = 0;

		reset_options();
	}

	void EndPhase::entered_phase(const Socket & socket, const Player & player)
	{
		in_phase++;
		//print_info(socket, player);
		countPoints(socket, player);
	}

	void EndPhase::countPoints(const Socket & socket, const Player & player)
	{
		if (player1Score == -1 && player2Score == -1 && in_phase == 2) {
			auto& game = state()->game();

			player1Score = game.getPlayers().at(0)->get_player().score();
			player2Score = game.getPlayers().at(1)->get_player().score();

			if (player1Score == player2Score) {
				player1Score = game.getPlayers().at(0)->get_player().building_score();
				player2Score = game.getPlayers().at(1)->get_player().building_score();
			}

			std::ostringstream scores;

			scores << "Scores;\r\n";
			scores << "- " << game.getPlayers().at(0)->get_player().name() << ": " << player1Score << "\r\n";
			scores << "- " << game.getPlayers().at(1)->get_player().name() << ": " << player2Score << "\r\n";

			state()->broadcast(scores.str());

			if (player1Score > player2Score) {
				state()->broadcast(game.getPlayers().at(0)->get_player().name() + " is the winner!\r\n");
			}
			else {
				state()->broadcast(game.getPlayers().at(1)->get_player().name() + " is the winner!\r\n");
			}

			state()->broadcast("Quit and reconnect to start another game.");
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