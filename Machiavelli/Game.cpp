#include "Game.h"
#include <algorithm>
#include <random>
#include "util\RandomGenerator.h"

using util::RandomGenerator;

namespace machiavelli
{
	Game::Game()
	{
		for (int i = 0; i < 4; i++) {
			building_deck.push_top_stack(BuildingCard{ "flat", 10_g, [](Player& p) {} , [](Game& g) {} });
		}
		for (int i = 0; i < 4; i++) {
			building_deck.push_top_stack(BuildingCard{ "flat", 20_g, [](Player& p) {} , [](Game& g) {} });
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

	Player & Game::getPlayerByIndex(size_t pIndex)
	{
		auto clientInfo = players.at(pIndex);

		return clientInfo->get_player();
	}

	Player & Game::getKing()
	{
		return getPlayerByIndex(kingIndex);
	}


	bool Game::started() const
	{
		return _started;
	}
}
