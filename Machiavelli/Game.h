#pragma once
#include "Player.h"
#include <vector>
#include <memory>
#include "network\ClientInfo.h"
#include "cards\CharacterCard.h"
#include "cards\BuildingCard.h"
namespace machiavelli
{
	class Game
	{
	public:
		Game();
		~Game();

		void start();

		bool addPlayer(std::shared_ptr<ClientInfo> player);

		bool started() const;

		void shuffleDecks();

	private:
		void tick();

		std::vector<std::shared_ptr<ClientInfo>> players;

		std::vector<BuildingCard> building_deck;
		std::vector<CharacterCard> character_deck;

		bool _started = false;
		int turn_count = 0;
	};
}
