#pragma once
#include "..\Gold.h"
#include "CardCategory.h"
#include <string>
#include <istream>
#include "..\CardEffect.h"

namespace machiavelli
{
	class BuildingCard
	{
	public:
		BuildingCard() {};
		BuildingCard(const std::string& name, const Gold& cost, CardEffect effect, CardAction action);
		
		BuildingCard& operator=(const BuildingCard& other);

		operator const Gold&() const;

		const Gold& cost() const;
		const std::string& name() const;
		const std::string& description() const;

		void operator () (Game& game);
		void operator () (Player& player);

	private:
		Gold _cost{ 1_g };
		std::string _name{ "<no name>" };
		std::string _description{ "" };
		CardCategory _category{ CardCategory::none() };
		CardEffect _effect;
		CardAction _action;

		friend std::istream & operator>>(std::istream & os, BuildingCard & gold);
	};

	std::istream& operator>>(std::istream& os, BuildingCard& gold);
}

