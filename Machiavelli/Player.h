#pragma once
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

		bool operator==(const Player& pOther) const;
		bool operator!=(const Player& pOther) const;

		Gold& gold();
		const Gold& gold() const;

		const std::string& name() const;
		void name(std::string name);

		void addBuildingCardToDeck(const building_card& pCard);

		void addCharacterCardToDeck(const character_card& pCard);
		building_card drawFromBuildingDeck();
		character_card drawFromCharacterDeck();
		building_card_deck getPlayerBuildingCards() const;
		character_card_deck getPlayerCharacterCards() const;

		int draw_per_turn() const;
		void draw_per_turn(int new_value);

		void apply_card_effects();

	private:
		Gold _gold{ 0_g };
		std::string player_name{ "<no name>" };

		building_card_deck building_cards;
		character_card_deck character_cards;

		int _draw_per_turn = 2;
	};

	std::ostream& operator<<(std::ostream& os, const Player& gold);
}

