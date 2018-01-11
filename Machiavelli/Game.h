#pragma once
#include "Player.h"
#include <vector>
#include <memory>
#include "network\ClientInfo.h"
#include "cards\CharacterCard.h"
#include "cards\BuildingCard.h"
#include "Deck.h"
#include <map>

namespace machiavelli
{
	class Game
	{
	public:
		Game();
		~Game();

		void start();
		void doTurn();

		bool addPlayer(std::shared_ptr<ClientInfo> player);
		Player& getPlayerByIndex(size_t pIndex);
		Player& getPlayerByName(const std::string& name) const;

		void setKing();
		Player& getKing();

		bool started() const;

		void replace_deck(Deck<BuildingCard>& other);
		void replace_deck(Deck<CharacterCard>& other);

		std::vector<BuildingCard> drawAmountOfBuildingCards(int amountOfCards);
		std::vector<CharacterCard> drawAmountOfCharacterCards(int amountOfCards);

		CharacterCard drawCharacterCard();
		BuildingCard drawBuildingCard();

		void addCardtoTableDeck(const CharacterCard& pCard);

		void giveAmountOfBuildingCardsToPlayer(Player& player, int amount);

		void shuffleCharacterCards();
		void shuffleBuildingCards();

		std::shared_ptr<ClientInfo> current_player() const;
		void next_player();

		void broadcast(const std::string & message);

		std::map<std::string, CharacterCard> drawn_character_card(const Player& exclude, const std::string& exclude_card) const;
		Player& get_other_player(Player& me) const;

		void discard_card(BuildingCard && card);

	private:
		void tick();

		std::vector<std::shared_ptr<ClientInfo>> players;

		Deck<BuildingCard> building_deck;
		Deck<CharacterCard> character_deck;
		Deck<CharacterCard> table_deck;

		size_t _current_player = 0llu;

		bool _started = false;
		int turn_count = 0;
		size_t kingIndex = 0llu;
	};
}
