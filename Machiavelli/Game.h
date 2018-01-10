#pragma once
#include "Player.h"
#include <vector>
#include <memory>
#include "network\ClientInfo.h"
#include "cards\CharacterCard.h"
#include "cards\BuildingCard.h"
#include "Deck.h"

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
		Player& getKing();

		bool started() const;

		void replace_building_deck(Deck<BuildingCard>& other);
		void replace_character_deck(Deck<CharacterCard>& other);

	private:
		void tick();
		void setKing();

		std::vector<std::shared_ptr<ClientInfo>> players;

		Deck<BuildingCard> building_deck;
		Deck<CharacterCard> character_deck;

		bool _started = false;
		int turn_count = 0;
		size_t kingIndex = 0llu;
	};
}
