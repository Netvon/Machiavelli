#pragma once

#include <string>
#include "../CardEffect.h"
#include <map>

namespace machiavelli {
	class CharacterCard
	{
	public:
		CharacterCard();
		CharacterCard(const std::string& name, const unsigned int order, CardEffect effect);
		~CharacterCard();

		CharacterCard & operator=(const CharacterCard & other);
		bool operator==(const CharacterCard& pOther);

		const std::string& name() const;
		bool getIsVisible() const;
		void setIsVisible(bool pIsVisible);
		unsigned int getOrder() const;

		CardEffect effect() const;

		void operator() (Player& player);

		bool is_murdered() const;
		void is_murdered(bool new_value);

		bool empty() const;

		static std::string get_name_by_order(unsigned int order);

	private:
		std::string _name{ "<no name>" };
		CardEffect _effect;
		unsigned int order = 0;
		bool isVisible = true;

		bool _murdered = false;

		friend std::istream& operator>>(std::istream& is, CharacterCard& card);

		static std::map<unsigned int, std::string> names_by_order;
	};

	std::istream& operator>>(std::istream& is, CharacterCard& card);
}

