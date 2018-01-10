#include "CharacterCard.h"

namespace machiavelli {

	CharacterCard::CharacterCard()
	{
	}

	CharacterCard::CharacterCard(const std::string & name)
		:_name(name)
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
}
