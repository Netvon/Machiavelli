#pragma once
#include "cards\BuildingCard.h"
#include "cards\CharacterCard.h"
#include "Gold.h"
#include "Deck.h"
#include <memory>
#include <vector>
#include "util\RandomGenerator.h"
#include <string>
#include <unordered_set>
#include <set>

namespace machiavelli {
	class Player
	{
	public:
		using building_card = BuildingCard;
		using character_card = CharacterCard;
		using building_card_deck = Deck<building_card>;
		using character_card_deck = Deck<character_card>;

		Player();
		Player(const std::string& name);
		~Player() = default;

		bool operator==(const Player& pOther) const;
		bool operator!=(const Player& pOther) const;

		Gold& gold();
		const Gold& gold() const;

		const std::string& name() const;
		void name(const std::string& name);

		void addBuildingCardToDeck(const building_card& pCard);
		void addBuildingCardToDeck(building_card&& pCard);
		void addCharacterCardToDeck(const character_card& pCard);

		void discardBuildingCardFromDeck(const building_card& pCard);
		void discardCharacterCardFromDeck(const character_card& pCard);

		building_card drawFromBuildingDeck();
		character_card drawFromCharacterDeck();

		building_card_deck getPlayerBuildingCards() const;
		character_card_deck getPlayerCharacterCards() const;

		bool hasCharacterCardByOrder(unsigned int pOrder);
		const character_card findCardByOrder(unsigned int pOrder) const;

		int draw_per_turn() const;
		void draw_per_turn(int new_value);

		int build_per_turn() const;
		void build_per_turn(int new_value);

		bool has_character(const std::string& character);

		void apply_card_effects();
		void reset_effects();

		void kill_character(const std::string& name);

		void swap_building_cards(Player& player);

		void discard_character_cards();

		std::vector<building_card> built_buildings();
		void built_building(const building_card & pCard);
		size_t building_card_amount() const;
		void destroy_building(const std::string& name);

		void finished_first(bool new_value);
		int score() const;
	private:
		int id{ util::random(0, 1000) };

		Gold _gold{ 0_g };
		std::string player_name{ def::NO_NAME_SET };

		building_card_deck building_cards;
		character_card_deck character_cards;

		int _draw_per_turn = 2;
		int _build_per_turn = 1;

		bool _finished_first = false;

		std::unordered_set<std::string> protected_against;
	};

	std::ostream& operator<<(std::ostream& os, const Player& gold);
}

