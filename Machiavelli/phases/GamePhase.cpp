#include "GamePhase.h"
#include "PlayPhase.h"
using namespace std::placeholders;

namespace machiavelli
{
	GamePhase::GamePhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
		enable_defaults();
	}

	void GamePhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void GamePhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the GamePhase!\r\n";

		nextTurn(socket, player);

		print_info(socket, player);
	}

	void GamePhase::reset()
	{
		reset_options();
	}

	void GamePhase::handle_character_cards(const Socket & socket, Player & player)
	{
		auto& game = state()->game();
		game.shuffleCharacterCards();
		CharacterCard drawnCard = game.drawCharacterCard();

		if (!drawnCard.is_empty()) {
			socket << "You have drawn this card: " << drawnCard.name() <<  "\r\n";
			socket << "This card will put face-down on the table." << "\r\n";
			game.addCardtoTableDeck(drawnCard);
			characterCardsDrawn = true;
		}

		reset_options(true);

		add_option("0", "Draw a Character Card", [=](const auto& a, auto& b) {
			auto& game = state()->game();

			reset_options(true);

			CharacterCard characterCard = game.drawCharacterCard();

			if (!characterCard.is_empty()) {
				a << "You have drawn this card: " << characterCard.name() << "\r\n";
				if (characterCard.name() == "Koning") {
					if (game.getKing()->get_player() != b) {
						game.nextPlayerIsKing();
					}
					a << "You are the King now!\r\n";
				}
				a << "You will be able to hold this card. De deck will now be passed to the other player." << "\r\n";
				b.addCharacterCardToDeck(characterCard);
			}

			print_info(a, b);

			game.next_player();
			game.broadcast("It's " + game.current_player()->get_player().name() + "'s turn!\r\n");
			nextTurn(game.current_player()->get_socket(), game.current_player()->get_player());

		}, true);

		print_info(socket, player);
	}

	void GamePhase::nextTurn(const Socket & socket, const Player & player)
	{
		auto& game = state()->game();
		auto& currentPlayer = game.current_player()->get_player();

		if (!game.isCharacterDeckEmpty()) {
			if (currentPlayer == game.getKing()->get_player() || currentPlayer == player) {
				add_option("0", "Draw a Character Card", std::bind(&GamePhase::handle_character_cards, this, _1, _2), true);
			}
		}
		else {
			//state()->add_phase<PlayPhase>("play");
			state()->navigate_to("play");
		}
	}
}