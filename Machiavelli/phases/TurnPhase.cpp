#include "TurnPhase.h"
#include "../cards/CardActions.h"
using namespace std::placeholders;

namespace machiavelli
{
	void TurnPhase::check_next_turn()
	{
		if (usedCharacterAction && (gotGold || takenBuildingCards)) {
			gotGold = false;
			builtBuilding = false;
			takenBuildingCards = false;
			usedCharacterAction = false;
			discardedBuildingCard = false;
			takingBuildingCardsNow = false;
			usingCharacterAction = false;
			disable_end = false;
			disable_top = false;
			newTurn = true;

			auto next_character_pos = state()->getCharacterPosition() + 1;
			//auto max_character_pos = static_cast<unsigned int>(CharacterCard::loaded_amount());

			state()->changeCharacterOrder(next_character_pos);

			// true als alle characters zijn opgeroepen.
			// er is dan een speelronde gedaan.
			// alle effecten worden gereset
			/*if (next_character_pos > max_character_pos) {
				for (auto player : state()->game().getPlayers()) {
					player->get_player().reset_effects();
					player->get_player().discard_character_cards();
				}

				state()->navigate_to("game");
			}
			else {
				state()->navigate_to("play");
			}*/

			
		}
	}

	TurnPhase::TurnPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
		enable_defaults();
	}

	void TurnPhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void TurnPhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the TurnPhase!\r\n";
		/*auto currentPosition = state()->getCharacterPosition();
		auto& game = state()->game();
		auto& currentPlayer = game.current_player()->get_player();*/

		//reset_options(true);

		//nextTurn(socket, player);

		if (state()->is_new_turn()) {

			for (auto player : state()->game().getPlayers()) {
				player->get_player().apply_card_effects();
			}
		}

		if (newTurn) {
			reset_options(true);
			newTurn = false;
		}

		print_info(socket, player);
	}

	void TurnPhase::add_options()
	{
		auto cphase = std::type_index(typeid(*state()->current_phase()));
		auto wanted_phase = std::type_index(typeid(TurnPhase));

		if ((usingCharacterAction || takingBuildingCardsNow || buildingBuilding) && !disable_top) {
			add_option("top", "Return the top menu", [&](const Socket& s, Player& p) {
				usingCharacterAction = false;
				takingBuildingCardsNow = false;
				buildingBuilding = false;

				check_next_turn();

				reset_options(true);
				print_info(s, p);

				
			}, true);
		}

		if (!disable_end) {
			add_option("end", "Go to the next Character", [&](const Socket& s, Player& p) {
				usedCharacterAction = true;
				gotGold = true;
				takenBuildingCards = true;

				reset_options(true);
				check_next_turn();
			}, true);
		}

		if (!takingBuildingCardsNow && !usingCharacterAction && !buildingBuilding && cphase == wanted_phase) {
			auto currentPosition = state()->getCharacterPosition();
			auto& game = state()->game();
			auto& currentPlayer = game.current_player()->get_player();

			auto& socket = state()->current_player()->get_socket();

			auto& current_card = currentPlayer.findCardByOrder(currentPosition);

			if (current_card.name() == def::NO_NAME_SET) {
				// TODO: fix de no-names
				// kan te maken hebben met het te ver doorlopen van de CharacterPosition...
				auto break_me = "here";
			}

			socket << "Je bent nu de: " << current_card.name() << "\r\n";

			/*auto effect = current_card.effect();
			if (effect) {
				effect(currentPlayer);
			}*/

			if (!actions::card_has_action(current_card.name()) || current_card.is_murdered()) {
				usedCharacterAction = true;
			}

			if (!usedCharacterAction) {
				add_option("0", "Gebruik het karaktereigenschap van de " + current_card.name(), [&, current_card](const Socket& s, Player& p) {

					usingCharacterAction = true;

					reset_options(true);

					machiavelli::actions::add_actions_for(current_card, state()->current_phase(), [this]() {
						usingCharacterAction = false;
						usedCharacterAction = true;
						reset_options(true);

						check_next_turn();
					});

					print_info(s, p);

				}, true);
			}

			if (!gotGold) {
				add_option("1", "Pak 2 goudstukken", std::bind(&TurnPhase::handle_get_gold, this, _1, _2), true);
			}

			if (!takenBuildingCards) {
				add_option("2", "Pak 2 bouwkaarten en leg er 1 af", std::bind(&TurnPhase::handle_take_buildingcards, this, _1, _2), true);
			}

			if (!builtBuilding && !currentPlayer.getPlayerBuildingCards().stackIsEmpty()) {
				machiavelli::actions::add_build_options(state()->current_phase(), [this]() {
					buildingBuilding = true;
				}, [this]() {
					builtBuilding = true;
					buildingBuilding = false;
					reset_options(true);

					check_next_turn();
				});
			}
		}
	}

	void TurnPhase::reset()
	{
		gotGold = false;
		builtBuilding = false;
		takenBuildingCards = false;
		usedCharacterAction = false;
		discardedBuildingCard = false;
		takingBuildingCardsNow = false;
		usingCharacterAction = false;
		disable_end = false;
		disable_top = false;
		newTurn = true;

		reset_options();
	}

	void TurnPhase::handle_get_gold(const Socket & socket, Player & player)
	{
		auto& game = state()->game();

		if (!gotGold) {
			player.gold() += 2_g;
			gotGold = true;;
			takenBuildingCards = true;

			reset_options(true);
		}
		else {
			socket << "Je hebt al goud gepakt!";
		}

		check_next_turn();
	}

	void TurnPhase::handle_take_buildingcards(const Socket & socket, Player & player)
	{
		disable_end = true;
		disable_top = true;

		takingBuildingCardsNow = true;
		auto& game = state()->game();
		
		BuildingCard card1 = game.drawBuildingCard();
		BuildingCard card2 = game.drawBuildingCard();

		socket << "Je hebt " << card1.name() << " en " << card2.name() << " gekregen. Welke leg je af?\r\n";

		reset_options();

		add_option("0", "Discard " + card1.all_info(), [this, card1, card2](const auto& a, auto& b) {
			auto& game = state()->game();

			takenBuildingCards = true;
			takingBuildingCardsNow = false;
			gotGold = true;

			disable_end = false;
			disable_top = false;

			game.discard_card(card1);
			b.addBuildingCardToDeck(card2);

			reset_options();
			check_next_turn();

			print_info(a, b);

		}, true);

		add_option("1", "Discard " + card2.all_info(), [this, card1, card2](const auto& a, auto& b) {
			auto& game = state()->game();

			takenBuildingCards = true;
			takingBuildingCardsNow = false;
			gotGold = true;

			disable_end = false;
			disable_top = false;

			game.discard_card(card2);
			b.addBuildingCardToDeck(card1);

			reset_options();
			check_next_turn();

			print_info(a, b);

		}, true);

		print_info(socket, player);
	}

	void TurnPhase::nextTurn(const Socket & socket, const Player & player)
	{
		
	}
}