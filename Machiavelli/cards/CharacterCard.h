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
		unsigned int getOrder() const;

		CardEffect effect() const;

		bool is_murdered() const;
		void is_murdered(bool new_value);

	private:
		std::string _name{ "<no name>" };
		CardEffect _effect;
		unsigned int order = 0;
		bool isVisible = true;

		bool _murdered = false;

		friend std::istream& operator>>(std::istream& is, CharacterCard& card);
	};

	std::istream& operator>>(std::istream& is, CharacterCard& card);
}

