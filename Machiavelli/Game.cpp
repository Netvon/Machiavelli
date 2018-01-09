#include "Game.h"
#include <algorithm>
#include <random>

namespace machiavelli
{
	Game::Game()
	{
	}

	Game::~Game()
	{
	}

	void Game::start()
	{
		_started = true;

		shuffleDecks();

		for (auto& player : players) {
			auto& p = player->get_player();

			p.gold() = 2_g;

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

	void Game::shuffleDecks()
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(building_deck.begin(), building_deck.end(), g);
		std::shuffle(character_deck.begin(), character_deck.end(), g);
	}

	void Game::giveBuildingCards()
	{
		
	}
}
