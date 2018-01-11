#include "GamePhase.h"
using namespace std::placeholders;

namespace machiavelli
{
	GamePhase::GamePhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_options();
	}

	GamePhase::~GamePhase()
	{
	}

	void GamePhase::print(const Socket & socket, const Player & player)
	{
	}

	void GamePhase::entered_phase(const Socket & socket, const Player & player)
	{
		socket << "Welcome to the GamePhase!\r\n";
	}

	void GamePhase::add_options()
	{
		auto game = state()->game();

		if (game.current_player()->get_player() == game.getKing()) {
			add_option("Pak 2 character kaarten", "character card command", std::bind(&GamePhase::handle_character_cards, this, _1, _2), true);
		}
	}

	void GamePhase::handle_character_cards(const Socket & socket, Player & player)
	{
		auto game = state()->game();
		std::vector<CharacterCard> drawnCards = game.drawAmountOfCharacterCards(2);

		socket << "Je hebt deze twee kaarten getrokken: " << drawnCards.at(0).name() << " en " << drawnCards.at(1).name();

		add_option("0", "Leg een character kaart af", [=](const auto& a, auto& b) {

			reset_options(false);
		}, true);
	}
}