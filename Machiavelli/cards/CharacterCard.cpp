#include "CharacterCard.h"
#include "..\Effects.h"

namespace machiavelli {

	std::map<unsigned int, std::string> CharacterCard::names_by_order;
	std::map<std::string, CharacterCard> CharacterCard::loaded;

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

	bool CharacterCard::is_empty() const
	{
		return _name == def::NO_NAME_SET;
	}

	std::string CharacterCard::get_name_by_order(unsigned int order)
	{
		return CharacterCard::names_by_order.at(order);
	}

	CharacterCard CharacterCard::get_by_name(std::string name)
	{
		return loaded.at(name);
	}

	std::size_t CharacterCard::loaded_amount()
	{
		return loaded.size();
	}

	const CardCategory & CharacterCard::category() const
	{
		return _category;
	}

	std::istream & operator>>(std::istream & is, CharacterCard & card)
	{
		std::istream::sentry s(is);

		if (s) {
			std::string order_string;
			std::string name;
			CardEffect effect;
			std::string category_string;
			CardCategory category;

			unsigned int order{ 0 };

			std::getline(is, order_string, ';');
			std::getline(is, name, ';');
			std::getline(is, category_string, '\n');

			if (!order_string.empty() && !name.empty() && !category_string.empty()) {
				try
				{
					effect = machiavelli::effects::CardEffectFactory(name);
					order = std::stoi(order_string);
					category = CardCategory(category_string);
				}
				catch (const std::exception&)
				{
					is.setstate(is.badbit);
					return is;
				}

				card._name = name;
				card.order = order;
				card._effect = effect;
				card._category = category;

				CharacterCard::names_by_order.insert_or_assign(order, name);
				CharacterCard::loaded.insert_or_assign(name, card);

				is.setstate(is.goodbit);
			}
		}

		return is;
	}
}
