#include "PlayPhase.h"
#include "TurnPhase.h"
#include "EndPhase.h"

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

	void PlayPhase::checkWin()
	{
		auto& game = state()->game();

		for (auto& player : game.getPlayers()) {
			auto& p = player->get_player();

			if (p.built_buildings().size() == 8) {
				game.broadcast(p.name() + " heeft 8 gebouwen gebouwd! De punten worden nu geteld.");
				state()->add_phase<EndPhase>("end");
				state()->navigate_to("end");
			}
		}
	}

	void PlayPhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void PlayPhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the PlayPhase!\r\n";

		//nextTurn(socket, player);

		reset_options(true);
	}

	void PlayPhase::add_options()
	{
		//auto& game = state()->game();
		//auto& currentPlayer = game.current_player()->get_player();

		//if (currentPlayer == game.getKing()) {
			add_option("0", "Roep volgende karakter op", std::bind(&PlayPhase::handle_turn, this, _1, _2), true);
		//}
	}

	void PlayPhase::handle_turn(const Socket & socket, const Player & player)
	{
		auto& game = state()->game();
		auto characterPosition = state()->getCharacterPosition();

		for (auto& player : game.getPlayers()) {
			auto& p = player->get_player();
			auto characterCards = p.getPlayerCharacterCards();

			if (p.hasCharacterCardByOrder(characterPosition)) {
				game.current_player(p.name());
				game.broadcast(p.name() + " is nu aan de beurt!\r\n");
				reset_options(false);

				state()->add_phase<TurnPhase>("turn");
				state()->navigate_to("turn");
				return;
			}
		}

		//if (characterPosition < 8) {
		state()->changeCharacterOrder(characterPosition + 1);
		/*}
		else {
			state()->changeCharacterOrder(1);
		}*/

		print_info(socket, player);
	}



	void PlayPhase::nextTurn(const Socket & socket, const Player & player)
	{
		
	}
}