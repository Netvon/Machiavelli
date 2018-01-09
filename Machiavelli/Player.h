#pragma once
#include ".\cards\Card.h"
#include "cards\BuildingCard.h"
#include "Gold.h"
#include <memory>
#include <vector>
#include <string>

namespace machiavelli {
	class Player
	{
	public:
		typedef std::shared_ptr<BuildingCard> building_card;
		typedef std::vector<building_card> building_card_deck;

		Player();
		Player(const std::string& name);
		~Player() = default;

		Gold& gold();
		const Gold& gold() const;

		const std::string& name() const;
		void name(std::string name);

		


	private:
		Gold _gold{ 0_g };
		std::string player_name{ "<no name>" };

		building_card_deck building_cards;
	};

	std::ostream& operator<<(std::ostream& os, const Player& gold);
}

