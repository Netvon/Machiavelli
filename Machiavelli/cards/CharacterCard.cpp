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

	const std::string & CharacterCard::name() const
	{
		return _name;
	}

	bool CharacterCard::getIsVisible() const
	{
		return isVisible;
	}
}
