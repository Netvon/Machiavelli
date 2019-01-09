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

	void PlayPhase::checkWin()
	{
		auto& game = state()->game();

		for (auto& player : game.getPlayers()) {
			auto& p = player->get_player();

			if (p.built_buildings().size() >= 8) {
				game.broadcast(p.name() + " heeft 8 gebouwen gebouwd! De punten worden nu geteld.\r\n");

				state()->navigate_to("end");
				return;
			}
		}
	}

	void PlayPhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void PlayPhase::entered_phase(const Socket & socket, const Player & player)
	{
		checkWin();

		socket << "Welcome to the PlayPhase!\r\n";

		//nextTurn(socket, player);

		reset_options(true);
		print_info(socket, player);
	}

	void PlayPhase::add_options()
	{
		//auto& game = state()->game();
		//auto& currentPlayer = game.current_player()->get_player();

		//if (currentPlayer == game.getKing()) {
			add_option("0", "Roep volgende karakter op", std::bind(&PlayPhase::handle_turn, this, _1, _2), true);
		//}
	}

	void PlayPhase::reset()
	{
		reset_options();
	}

	void PlayPhase::handle_turn(const Socket & socket, const Player & player)
	{
		auto& game = state()->game();
		auto characterPosition = state()->getCharacterPosition();
		auto card_name = CharacterCard::get_name_by_order(characterPosition);

		bool someone_has_card = false;

		game.broadcast("Calling " + card_name + " to action.\r\n");

		for (auto& player : game.getPlayers()) {
			auto& p = player->get_player();

			if (p.hasCharacterCardByOrder(characterPosition)) {
				game.current_player(p.name());
				game.broadcast(p.name() + " is nu aan de beurt!\r\n");

				someone_has_card = true;
				break;
			}
		}


		if (someone_has_card) {
			
			state()->navigate_to("turn");

		}
		else {

			state()->changeCharacterOrder(characterPosition + 1);
			game.broadcast("Nobody has the " + card_name + " card.\r\n");
			print_info(socket, player);

		}
		
	}

	void PlayPhase::nextTurn(const Socket & socket, const Player & player)
	{
		
	}
}