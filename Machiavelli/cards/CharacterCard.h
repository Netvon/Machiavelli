#pragma once

#include <string>
#include "../CardEffect.h"

namespace machiavelli {
	class CharacterCard
	{
	public:
		CharacterCard();
		CharacterCard(const std::string& name, const unsigned int order, CardEffect effect);
		~CharacterCard();

		bool operator==(const CharacterCard& pOther);

		const std::string& name() const;
		bool getIsVisible() const;
		void setIsVisible(bool pIsVisible);

		CardEffect effect() const;

	private:
		std::string _name{ "<no name>" };
		CardEffect _effect;
		unsigned int order = 0;
		bool isVisible = true;

		friend std::istream& operator>>(std::istream& is, CharacterCard& card);
	};

	std::istream& operator>>(std::istream& is, CharacterCard& card);
}

