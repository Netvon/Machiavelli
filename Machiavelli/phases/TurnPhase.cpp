#include "TurnPhase.h"
#include "../cards/CardActions.h"
using namespace std::placeholders;

namespace machiavelli
{
	TurnPhase::TurnPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
		enable_defaults();
	}

	TurnPhase::~TurnPhase()
	{
	}

	void TurnPhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void TurnPhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the TurnPhase!\r\n";
		auto currentPosition = state()->getCharacterPosition();
		auto& game = state()->game();
		auto& currentPlayer = game.current_player()->get_player();

		if (currentPlayer == player) {
			auto& current_card = player.findCardByOrder(currentPosition);
			bool empty = current_card.empty();

			socket << "Je bent nu de: " << current_card.name() << "\r\n";

			auto effect = current_card.effect();
			if(effect)
				effect(currentPlayer);

			if (!usedCharacterAction) {
				add_option("0", "Gebruik het karaktereigenschap van de " + current_card.name(), [&, current_card](const Socket& s, Player& p) {

					reset_options(true);

					machiavelli::actions::add_actions_for(current_card, state()->current_phase());

					print_info(s, p);

				}, true);
			}

			if (!gotGold) {
				add_option("1", "Pak 2 goudstukken", std::bind(&TurnPhase::handle_get_gold, this, _1, _2), true);
			}

			if (!takenBuildingCards) {
				add_option("2", "Pak 2 bouwkaarten en leg er 1 af", std::bind(&TurnPhase::handle_take_buildingcards, this, _1, _2), true);
			}
		}

		nextTurn(socket, player);
	}

	void TurnPhase::add_options()
	{
		
	}

	void TurnPhase::handle_get_gold(const Socket & socket, Player & player)
	{
		auto& game = state()->game();

		if (!gotGold) {
			player.gold() += 2_g;
			gotGold = true;
		}
	}

	void TurnPhase::handle_take_buildingcards(const Socket & socket, Player & player)
	{
		auto& game = state()->game();
		
		BuildingCard card1 = game.drawBuildingCard();
		BuildingCard card2 = game.drawBuildingCard();

		if (!discardedBuildingCard) {
			socket << "Je hebt " << card1.name() << " en " << card2.name() << " gekregen. Welke leg je af?\r\n";

			reset_options(true);

			add_option("0", card1.name(), [this, &game, card1, card2](const auto& a, auto& b) {
				auto& game = state()->game();

				reset_options(true);

				if (!discardedBuildingCard) {
					game.discard_card(card1);
					b.addBuildingCardToDeck(card2);
				}
				discardedBuildingCard = true;

			}, true);

			add_option("1", card2.name(), [this, &game, card1, card2](const auto& a, auto& b) {
				auto& game = state()->game();

				reset_options(true);

				if (!discardedBuildingCard) {
					game.discard_card(card2);
					b.addBuildingCardToDeck(card1);
				}
				discardedBuildingCard = true;

			}, true);

			print_info(socket, player);
		}
	}

	void TurnPhase::nextTurn(const Socket & socket, const Player & player)
	{
		
	}
}