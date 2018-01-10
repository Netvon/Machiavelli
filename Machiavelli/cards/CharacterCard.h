#pragma once

#include <string>

namespace machiavelli {
	class CharacterCard
	{
	public:
		CharacterCard();
		CharacterCard(const std::string& name);
		~CharacterCard();

		bool operator==(const CharacterCard& pOther);

		const std::string& name() const;
		bool getIsVisible() const;

	private:
		std::string _name{ "<no name>" };
		unsigned int order = 0;
		bool isVisible = true;

	};
}

