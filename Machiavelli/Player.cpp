#include "Player.h"

namespace machiavelli {

	Player::Player() { }

	Player::Player(const std::string& name)
		: player_name{ name }
	{

	}

	bool Player::operator==(const Player & pOther) const
	{
		return player_name == pOther.player_name && _gold == pOther._gold;
	}

	bool Player::operator!=(const Player & pOther) const
	{
		return player_name != pOther.player_name && _gold != pOther._gold;
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

	void Player::addBuildingCardToDeck(const building_card& pCard)
	{
		building_cards.push_top_stack(pCard);
	}

	void Player::addCharacterCardToDeck(const character_card & pCard)
	{
	}

	Player::building_card Player::drawFromBuildingDeck()
	{
		return building_cards.draw();
	}

	Player::character_card Player::drawFromCharacterDeck()
	{
		return character_cards.draw();
	}

	Player::building_card_deck Player::getPlayerBuildingCards() const
	{
		return building_cards;
	}

	Player::character_card_deck Player::getPlayerCharacterCards() const
	{
		return character_cards;
	}

	int Player::draw_per_turn() const
	{
		return _draw_per_turn;
	}

	void Player::draw_per_turn(int new_value)
	{
		_draw_per_turn = new_value;
	}

	int Player::build_per_turn() const
	{
		return _build_per_turn;
	}

	void Player::build_per_turn(int new_value)
	{
		_build_per_turn = new_value;
	}

	void Player::apply_card_effects()
	{
		for (auto& card : character_cards) {
			auto& me = *this;
			auto effect = card.effect();

			if (effect) {
				effect(me);
			}
		}
	}

	void Player::reset_effects()
	{
		_draw_per_turn = 2;
		_build_per_turn = 1;
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
