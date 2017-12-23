#include "Player.h"

namespace machiavelli {

	Player::Player() { }

	Player::Player(const std::string& name)
		: player_name{ name }
	{
	}

	const Player::gold_amount & Player::gold() const
	{
		return gold_pieces;
	}

	void Player::gold(gold_amount gold)
	{
		gold_pieces = gold;
	}

	const std::string & Player::name() const
	{
		return player_name;
	}

	void Player::name(std::string name)
	{
		player_name = name;
	}
}
