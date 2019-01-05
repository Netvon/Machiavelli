#include "Player.h"

namespace machiavelli {

	Player::Player() { }

	Player::Player(const std::string& name)
		: player_name{ name }
	{

	}

	bool Player::operator==(const Player & pOther) const
	{
		return id == pOther.id;
	}

	bool Player::operator!=(const Player & pOther) const
	{
		return id != pOther.id;
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

	void Player::name(const std::string& name)
	{
		player_name = name;
	}

	void Player::addBuildingCardToDeck(const building_card& pCard)
	{
		building_cards.push_top_stack(pCard);
	}

	void Player::addBuildingCardToDeck(building_card && pCard)
	{
		building_cards.push_top_stack(pCard);
	}

	void Player::addCharacterCardToDeck(const character_card & pCard)
	{
		character_cards.push_top_stack(pCard);
	}

	void Player::discardBuildingCardFromDeck(const building_card & pCard)
	{
		building_cards.discard(pCard);
	}

	void Player::discardCharacterCardFromDeck(const character_card & pCard)
	{
		character_cards.discard(pCard);
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

	Player::character_card_deck & Player::getPlayerCharacterCards()
	{
		return character_cards;
	}

	bool Player::hasCharacterCardByOrder(const unsigned int pOrder)
	{
		for (auto& card : character_cards) {
			if (card.getOrder() == pOrder && !card.is_murdered()) {
				return true;
			}
		}

		return false;
	}

	const Player::character_card Player::findCardByOrder(const unsigned int pOrder) const
	{
		for (auto& card : character_cards) {
			if (card.getOrder() == pOrder) {
				return card;
			}
		}

		return character_card();
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

	bool Player::has_character(const std::string & character)
	{
		auto result = std::find_if(character_cards.begin(), character_cards.end(), [character](const CharacterCard& card) {
			return card.name() == character;
		});

		return result != character_cards.end();
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

		protected_against.clear();

		for (auto& card : character_cards) {
			card.is_murdered(false);
		}
	}

	void Player::kill_character(const std::string & name)
	{
		for (auto& card : character_cards) {
			if (card.name() == name) {
				card.is_murdered(true);
			}
		}
	}

	void Player::swap_building_cards(Player & player)
	{
		if (player.building_cards.stackIsEmpty()) {
			return;
		}

		building_cards.swapStack(player.building_cards);
	}

	void Player::discard_character_cards()
	{
		character_cards = character_card_deck();
	}

	size_t Player::building_card_amount() const
	{
		return building_cards.size();
	}

	void Player::build_building(const building_card & pCard)
	{
		for (auto & card : building_cards) {

			if (card == pCard) {
				card.setIsBuilt(true);
				_gold -= card.cost();
			}
		}
	}

	int Player::unbuilt_buildings_amount() const
	{
		auto count = 0;
		for (const auto & card : building_cards) {

			if (!card.getIsBuilt()) {
				count++;
			}
		}

		return count;
	}

	void Player::destroy_building(const std::string & name)
	{
		if (name == "Kerker") {
			return;
		}

		for (auto & card : building_cards) {
			if (card.name() == name) {
				card.setIsBuilt(false);
			}
		}
	}

	void Player::finished_first(bool new_value)
	{
		_finished_first = new_value;
	}

	int Player::score() const
	{
		int temp = 0;
		std::set<CardCategory> has_categories;

		for (auto & card : building_cards) {
			if (card.getIsBuilt()) {
				temp += card.cost();

				if (card.name() == "Drakenpoort" || card.name() == "Universiteit") {
					temp += 2_g;
				}

				has_categories.insert(card.category());
			}
		}

		if (has_categories.size() >= CardCategory::total_amount()) {
			temp += 3;
		}

		if (_finished_first) {
			temp += 4;
		}

		return temp;
	}

	std::vector<Player::building_card> Player::built_buildings()
	{
		std::vector<Player::building_card> temp;
		for (auto & card : building_cards) {
			if (card.getIsBuilt()) {
				temp.push_back(card);
			}
		}
		return temp;
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
