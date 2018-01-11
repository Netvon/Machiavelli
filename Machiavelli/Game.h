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

		void replace_deck(Deck<BuildingCard>& other);
		void replace_deck(Deck<CharacterCard>& other);

		std::shared_ptr<ClientInfo> current_player() const;

	private:
		void tick();
		void setKing();

		std::vector<std::shared_ptr<ClientInfo>> players;

		Deck<BuildingCard> building_deck;
		Deck<CharacterCard> character_deck;

		size_t _current_player;

		bool _started = false;
		int turn_count = 0;
		size_t kingIndex = 0llu;
	};
}
