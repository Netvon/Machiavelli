#include "Game.h"
#include <algorithm>
#include <random>
#include "util\RandomGenerator.h"

using util::RandomGenerator;

namespace machiavelli
{
	Game::Game()
	{
		for (int i = 0; i < 8; i++) {
			building_deck.push_top_stack(BuildingCard{ "flat", Gold{ 10 }, CardEffect{}, CardAction{} });
		}
	}

	Game::~Game()
	{
	}

	void Game::start()
	{
		_started = true;

		building_deck.shuffleStack();

		for (auto& player : players) {
			auto& p = player->get_player();

			p.gold() = 2_g;
			
			for (int i = 0; i < 4; i++) {
				p.addCardToDeck(building_deck.draw());
			}
		}
	}

	bool Game::addPlayer(std::shared_ptr<ClientInfo> player)
	{
		if (players.size() >= 2) {
			return false;
		}

		players.push_back(player);

		if (players.size() == 2) {
			start();
		}

		return true;
	}	

	bool Game::started() const
	{
		return _started;
	}
}
