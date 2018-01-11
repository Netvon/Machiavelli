#pragma once

#include <string>

namespace machiavelli {
	class CharacterCard
	{
	public:
		CharacterCard();
		CharacterCard(const std::string& name, const unsigned int order);
		~CharacterCard();

		bool operator==(const CharacterCard& pOther);

		const std::string& name() const;
		bool getIsVisible() const;
		void setIsVisible(bool pIsVisible);

	private:
		std::string _name{ "<no name>" };
		unsigned int order = 0;
		bool isVisible = true;

		friend std::istream& operator>>(std::istream& is, CharacterCard& card);
	};

	std::istream& operator>>(std::istream& is, CharacterCard& card);
}

