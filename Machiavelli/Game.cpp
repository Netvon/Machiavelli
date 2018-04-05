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

	Player & Game::getPlayerByName(const std::string & name) const
	{
		for (auto player : players) {
			auto& p = player->get_player();

			if (p.name() == name) {
				return p;
			}
		}
	}

	std::vector<std::shared_ptr<ClientInfo>> Game::getPlayers() const
	{
		return players;
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

		if (building_deck.sizeOfStack() < amountOfCards) {
			current_player()->get_socket() << "Er zijn niet genoeg building kaarten meer.";
			return drawnCards;
		}

		for (int i = 0; i < amountOfCards; i++) {
			drawnCards.push_back(building_deck.draw());
		}

		return drawnCards;
	}

	std::vector<CharacterCard> Game::drawAmountOfCharacterCards(int amountOfCards)
	{
		// TODO: Als er geen kaarten zijn mag dit niet

		std::vector<CharacterCard> drawnCards;

		if (character_deck.sizeOfStack() < amountOfCards) {
			current_player()->get_socket() << "Er zijn niet genoeg character kaarten meer.";
			return drawnCards;
		}

		for (int i = 0; i < amountOfCards; i++) {
			drawnCards.push_back(character_deck.draw());
		}

		return drawnCards;
	}

	CharacterCard Game::drawCharacterCard()
	{
		if (character_deck.stackIsEmpty()) {
			current_player()->get_socket() << "Er zijn niet genoeg character kaarten meer.";
			return CharacterCard{};
		}

		return character_deck.draw();
	}

	BuildingCard Game::drawBuildingCard()
	{
		if (building_deck.stackIsEmpty()) {
			current_player()->get_socket() << "Er zijn niet genoeg building kaarten meer.";
			return BuildingCard{};
		}

		return building_deck.draw();
	}

	void Game::addCardtoTableDeck(const CharacterCard & pCard)
	{
		table_deck.push_top_stack(pCard);
	}

	void Game::giveAmountOfBuildingCardsToPlayer(Player & player, int amount)
	{
		// TODO: Als er geen kaarten zijn mag dit niet

		auto drawnCards = drawAmountOfBuildingCards(amount);

		for (auto& card : drawnCards) {
			player.addBuildingCardToDeck(card);
		}
	}

	void Game::shuffleCharacterCards()
	{
		character_deck.shuffleStack();
	}

	void Game::shuffleBuildingCards()
	{
		building_deck.shuffleStack();
	}

	bool Game::isCharacterDeckEmpty() const
	{
		return character_deck.stackIsEmpty();
	}

	bool Game::isBuildingDeckEmpty() const
	{
		return building_deck.stackIsEmpty();
	}

	std::shared_ptr<ClientInfo> Game::current_player() const
	{
		return players.at(_current_player);
	}

	void Game::current_player(const std::string & name)
	{
		size_t index = 0llu;
		for (auto player : players) {
			if (player->get_player().name() == name) {
				_current_player = index;
				return;
			} 

			index++;
		}
	}

	void Game::next_player()
{
		if (_current_player == 0llu) {
			_current_player = 1llu;
		}
		else {
			_current_player = 0llu;
		}
	}

	void Game::broadcast(const std::string & message)
	{
		for (auto player : players) {
			player->get_socket() << message;
		}
	}

	std::map<std::string, CharacterCard> Game::drawn_character_card(const Player& exclude, const std::string& exclude_card) const
	{
		std::map<std::string, CharacterCard> temp;

		for (auto player : players) {
			auto& p = player->get_player();

			if (p == exclude)
				continue;

			for (auto &card : p.getPlayerCharacterCards()) {
				if (card.name() == exclude_card)
					continue;

				temp.insert_or_assign(p.name(), card);
			}
		}

		return temp;
	}

	Player & Game::get_other_player(Player & me) const
	{
		for (auto player : players) {
			auto& p = player->get_player();

			if (p != me)
				return p;
		}
	}

	void Game::discard_card(BuildingCard && card)
	{
		building_deck.push_discard_top(std::move(card));
	}

	void Game::discard_card(const BuildingCard & card)
	{
		building_deck.push_discard_top(std::move(card));
	}

	void Game::setKing()
	{
		auto randomIndex = random(0llu, 1llu);

		kingIndex = randomIndex;
	}

	void Game::nextPlayerIsKing()
	{
		if (kingIndex == 0llu) {
			kingIndex = 1llu;
		}
		else {
			kingIndex = 0llu;
		}
	}
}
