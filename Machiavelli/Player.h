#pragma once
#include "Card.h"
#include <memory>
#include <vector>
#include <string>

namespace machiavelli {
	class Player
	{
	public:
		typedef std::shared_ptr<Card> card_type;
		typedef std::vector<card_type> card_storage;
		typedef unsigned int gold_amount;

		Player();
		Player(const std::string& name);
		~Player() = default;

		const gold_amount& gold() const;
		void gold(gold_amount gold);
		const std::string& name() const;
		void name(std::string name);
	private:
		card_storage cards;
		gold_amount gold_pieces;
		std::string player_name;
	};
}

