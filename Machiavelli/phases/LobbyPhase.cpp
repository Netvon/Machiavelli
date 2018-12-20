#include "LobbyPhase.h"
#include "GamePhase.h"
#include "PlayPhase.h"

namespace machiavelli
{
	LobbyPhase::LobbyPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
		//enable_defaults();
	}

	void LobbyPhase::print(const Socket & socket, const Player & player)
	{
	}

	void LobbyPhase::entered_phase(const Socket & socket, const Player & player)
	{
		amount_in_game++;

		if (amount_in_game >= 2) {

			if (!cheat_mode) {
				//state()->broadcast("Okay, that's two players! Let's begin.\r\n");
				state()->add_phase<machiavelli::GamePhase>("game");
				state()->navigate_to("game");
			}
			else {
				set_cheat_data();
			}

			amount_in_game = 0;
			cheat_mode = false;
			test_win = false;
			give_cards = false;
			test_effect = false;
		}
		else {
			socket << "There's not enough players yet.\n\r";
		}
	}

	void LobbyPhase::add_options()
	{
		add_option("cheat", "activate cheat-mode", [&](const auto& a, auto& b) {
			cheat_mode = true;
		});

		add_option("cheatcard", "activate cheat-mode and give buildingcards", [&](const auto& a, auto& b) {
			cheat_mode = true;
			give_cards = true;
		});

		add_option("cheataction", "activate cheat-mode and give buildingcards to test actions", [&](const auto& a, auto& b) {
			cheat_mode = true;
			give_cards = true;
			test_action = true;
		});

		add_option("cheatwin", "activate cheat-mode to test win", [&](const auto& a, auto& b) {
			cheat_mode = true;
			test_win = true;
		});

		add_option("cheateffect", "activate cheat-mode and give buildings", [&](const auto& a, auto& b) {
			cheat_mode = true;
			test_effect = true;
			give_cards = true;
		});
	}

	void LobbyPhase::set_cheat_data()
	{
		auto& game = state()->game();

		auto& p1 = game.getPlayerByIndex(0)->get_player();
		auto& p2 = game.getPlayerByIndex(1)->get_player();

		game.shuffleCharacterCards();
		game.shuffleBuildingCards();

		p1.gold() += 999;
		p2.gold() += 999;

		size_t card_amount = 0;
		if (give_cards)
			card_amount = 2;
		if (test_win)
			card_amount = 8;

		for (size_t i = 0; i < card_amount; i++)
		{
			p1.addBuildingCardToDeck(game.drawBuildingCard());
			p2.addBuildingCardToDeck(game.drawBuildingCard());
		}

		if (test_win || test_effect) {
			for (auto& card : p1.getPlayerBuildingCards()) {
				p1.built_building(card);
			}
		}

		if (test_action) {

			p1.addCharacterCardToDeck(machiavelli::CharacterCard::get_by_name("Moordenaar"));
			p1.addCharacterCardToDeck(machiavelli::CharacterCard::get_by_name("Dief"));

			p2.addCharacterCardToDeck(machiavelli::CharacterCard::get_by_name("Magi�r"));
			p2.addCharacterCardToDeck(machiavelli::CharacterCard::get_by_name("Condottiere"));

		}
		else {
			p1.addCharacterCardToDeck(game.drawCharacterCard());
			p1.addCharacterCardToDeck(game.drawCharacterCard());

			p2.addCharacterCardToDeck(game.drawCharacterCard());
			p2.addCharacterCardToDeck(game.drawCharacterCard());
		}


		state()->add_phase<machiavelli::PlayPhase>("play");
		state()->navigate_to("play");
	}
}
