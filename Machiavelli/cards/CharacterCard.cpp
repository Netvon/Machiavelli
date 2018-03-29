#include "CharacterCard.h"
#include "..\Effects.h"

namespace machiavelli {

	CharacterCard::CharacterCard()
	{
	}

	CharacterCard::CharacterCard(const std::string & name, const unsigned int order, CardEffect effect)
		:_name(name), order(order), _effect(effect)
	{
	}

	CharacterCard::~CharacterCard()
	{
	}

	CharacterCard & CharacterCard::operator=(const CharacterCard & other)
	{
		_name = other._name;
		order = other.order;
		_effect = other._effect;

		return *this;
	}

	bool CharacterCard::operator==(const CharacterCard & pOther)
	{
		return _name == pOther._name && order == pOther.order;
	}

	const std::string & CharacterCard::name() const
	{
		return _name;
	}

	bool CharacterCard::getIsVisible() const
	{
		return isVisible;
	}

	void CharacterCard::setIsVisible(bool pIsVisible)
	{
		isVisible = pIsVisible;
	}

	unsigned int CharacterCard::getOrder() const
	{
		return order;
	}

	CardEffect CharacterCard::effect() const
	{
		return _effect;
	}

	void CharacterCard::operator()(Player & player)
	{
		_effect(player);
	}

	bool CharacterCard::is_murdered() const
	{
		return _murdered;
	}

	void CharacterCard::is_murdered(bool new_value)
	{
		_murdered = new_value;
	}

	bool CharacterCard::empty() const
	{
		return _name == "<no name>";
	}

	std::istream & operator>>(std::istream & is, CharacterCard & card)
	{
		std::istream::sentry s(is);

		if (s) {
			std::string order_string;
			std::string name;
			CardEffect effect;

			unsigned int order{ 0 };

			std::getline(is, order_string, ';');
			std::getline(is, name, '\n');

			if (!order_string.empty() && !name.empty()) {
				try
				{
					effect = machiavelli::effects::CardEffectFactory(name);
					order = std::stoi(order_string);
				}
				catch (const std::exception&)
				{
					is.setstate(is.badbit);
					return is;
				}

				card._name = name;
				card.order = order;
				card._effect = effect;

				is.setstate(is.goodbit);
			}
		}

		return is;
	}
}
