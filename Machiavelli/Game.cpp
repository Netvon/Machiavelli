#include "Game.h"
#include <algorithm>
#include <random>
#include "util\RandomGenerator.h"

using util::RandomGenerator;

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

		building_deck.shuffleStack();

		for (auto& player : players) {
			auto& p = player->get_player();

			p.gold() = 2_g;
		}

		doTurn();
	}

	void Game::doTurn()
	{
		
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

	void Game::replace_deck(Deck<BuildingCard>& other)
	{
		building_deck.replace_deck(other);
	}

	void Game::replace_deck(Deck<CharacterCard>& other)
	{
		character_deck.replace_deck(other);
	}

	std::vector<BuildingCard> Game::drawAmountOfBuildingCards(int amountOfCards)
	{
		// TODO: Als er geen kaarten zijn mag dit niet

		std::vector<BuildingCard> drawnCards;

		for (int i = 0; i < amountOfCards; i++) {
			drawnCards.push_back(building_deck.draw());
		}

		return drawnCards;
	}

	std::vector<CharacterCard> Game::drawAmountOfCharacterCards(int amountOfCards)
	{
		// TODO: Als er geen kaarten zijn mag dit niet

		std::vector<CharacterCard> drawnCards;

		for (int i = 0; i < amountOfCards; i++) {
			drawnCards.push_back(character_deck.draw());
		}

		return drawnCards;
	}

	void Game::giveAmountOfBuildingCardsToPlayer(Player & player, int amount)
	{
		// TODO: Als er geen kaarten zijn mag dit niet

		auto drawnCards = drawAmountOfBuildingCards(amount);

		for (auto& card : drawnCards) {
			player.addBuildingCardToDeck(card);
		}
	}

	std::shared_ptr<ClientInfo> Game::current_player() const
	{
		return players.at(_current_player);
	}

	void Game::broadcast(const std::string & message)
	{
		for (auto player : players) {
			player->get_socket() << message;
		}
	}

	void Game::setKing()
	{
		auto randomIndex = random(0llu, 1llu);

		kingIndex = randomIndex;
	}
}
