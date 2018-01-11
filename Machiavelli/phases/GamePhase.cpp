#include "GamePhase.h"
using namespace std::placeholders;

namespace machiavelli
{
	GamePhase::GamePhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
		enable_defaults();
	}

	GamePhase::~GamePhase()
	{
	}

	void GamePhase::print(const Socket & socket, const Player & player)
	{
		print_info(socket, player);
	}

	void GamePhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the GamePhase!\r\n";

		nextTurn(socket, player);
	}

	void GamePhase::add_options()
	{
		
	}

	void GamePhase::handle_character_cards(const Socket & socket, Player & player)
	{
		auto& game = state()->game();
		game.shuffleCharacterCards();
		CharacterCard drawnCard = game.drawCharacterCard();

		if (drawnCard.name() != "<no name>") {
			socket << "Je hebt deze kaart getrokken: " << drawnCard.name() <<  "\r\n";
			socket << "Deze kaart wordt gedekt op tafel gelegd." << "\r\n";
			game.addCardtoTableDeck(drawnCard);
			characterCardsDrawn = true;
		}

		reset_options(true);

		add_option("0", "Pak een character kaart", [=](const auto& a, auto& b) {
			auto& game = state()->game();

			reset_options(true);

			CharacterCard characterCard = game.drawCharacterCard();

			if (characterCard.name() != "<no name>") {
				a << "Je hebt deze kaart getrokken: " << characterCard.name() << "\r\n";
				a << "Deze kaart krijg je in je hand. De stapel wordt nu doorgegeven." << "\r\n";
				b.addCharacterCardToDeck(characterCard);
			}

			print_info(a, b);

			game.next_player();
			game.broadcast(game.current_player()->get_player().name() + " is nu aan de beurt!");
			nextTurn(game.current_player()->get_socket(), game.current_player()->get_player());

		}, true);

		print_info(socket, player);
	}

	void GamePhase::nextTurn(const Socket & socket, const Player & player)
	{
		auto& game = state()->game();
		auto& currentPlayer = game.current_player()->get_player();

		if (!game.isCharacterDeckEmpty()) {
			if (currentPlayer == game.getKing() || currentPlayer == player) {
				add_option("0", "Pak character kaarten", std::bind(&GamePhase::handle_character_cards, this, _1, _2), true);
			}
		}
		else {
			state()->navigate_to("play");
		}
	}
}