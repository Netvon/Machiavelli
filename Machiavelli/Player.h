#pragma once
#include ".\cards\Card.h"
#include "cards\BuildingCard.h"
#include "cards\CharacterCard.h"
#include "Gold.h"
#include "Deck.h"
#include <memory>
#include <vector>
#include <string>

namespace machiavelli {
	class Player
	{
	public:
		typedef BuildingCard building_card;
		typedef CharacterCard character_card;
		typedef Deck<building_card> building_card_deck;
		typedef Deck<character_card> character_card_deck;

		Player();
		Player(const std::string& name);
		~Player() = default;

		bool operator==(const Player& pOther);

		Gold& gold();
		const Gold& gold() const;

		const std::string& name() const;
		void name(std::string name);

		void addBuildingCardToDeck(const building_card& pCard);
		void addCharacterCardToDeck(const character_card& pCard);
		building_card drawFromBuildingDeck();
		character_card drawFromCharacterDeck();

	private:
		Gold _gold{ 0_g };
		std::string player_name{ "<no name>" };

		building_card_deck building_cards;
		character_card_deck character_cards;
	};

	std::ostream& operator<<(std::ostream& os, const Player& gold);
}

