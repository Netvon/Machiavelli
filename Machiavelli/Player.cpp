#include "Player.h"

namespace machiavelli {

	Player::Player() { }

	Player::Player(const std::string& name)
		: player_name{ name }
	{

	}

	Gold & Player::gold()
	{
		return _gold;
	}

	const Gold & Player::gold() const
	{
		return _gold;
	}

	const std::string & Player::name() const
	{
		return player_name;
	}

	void Player::name(std::string name)
	{
		player_name = name;
	}

	std::ostream & operator<<(std::ostream & os, const Player & player)
	{
		std::ostream::sentry s(os);
		if (s) {
			os << player.name() << ": " << player.gold();
		}

		return os;
	}
}
