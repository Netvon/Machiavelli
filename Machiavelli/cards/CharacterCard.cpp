#include "CharacterCard.h"

namespace machiavelli {

	CharacterCard::CharacterCard()
	{
	}

	CharacterCard::CharacterCard(const std::string & name, const unsigned int order)
		:_name(name), order(order)
	{
	}

	CharacterCard::~CharacterCard()
	{
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

	std::istream & operator>>(std::istream & is, CharacterCard & card)
	{
		std::istream::sentry s(is);

		if (s) {
			std::string order_string;
			std::string name;

			unsigned int order{ 0 };

			std::getline(is, order_string, ';');
			std::getline(is, name, '\n');

			if (!order_string.empty() && !name.empty()) {
				try
				{
					order = std::stoi(order_string);
				}
				catch (const std::exception&)
				{
					is.setstate(is.badbit);
					return is;
				}

				card._name = name;
				card.order = order;

				is.setstate(is.goodbit);
			}
		}

		return is;
	}
}
