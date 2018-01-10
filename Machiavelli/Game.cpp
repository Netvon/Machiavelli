#include "Game.h"
#include <algorithm>
#include <random>
#include "util\RandomGenerator.h"
#include "util\CsvValue.h"

using util::RandomGenerator;
using util::CsvValue;

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

		for (int i = 0; i < 8; i++) {
			character_deck.push_top_stack(CharacterCard{ "Magier" });
		}
	}

	Game::~Game()
	{
	}

	void Game::start()
	{
		_started = true;

		building_deck.shuffleStack();
		setKing();

		for (auto& player : players) {
			auto& p = player->get_player();

			p.gold() = 2_g;
			
			for (int i = 0; i < 4; i++) {
				p.addBuildingCardToDeck(building_deck.draw());
			}
		}
	}

	void Game::doTurn()
	{
		for (auto& player : players) {
			auto& p = player->get_player();

			if (p == getKing()) {
				
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

	void Game::setKing()
	{
		auto randomIndex = random(0llu, 1llu);

		kingIndex = randomIndex;
	}
}
