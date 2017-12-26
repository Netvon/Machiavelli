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

		void operator () (Game& game);
		void operator () (Player& player);

	private:
		Gold _cost{ 1_g };
		std::string _name{ "<no name>" };
		CardCategory _category{ CardCategory::none() };
		CardEffect _effect;
		CardAction _action;
	};

	std::istream& operator>>(std::istream& os, BuildingCard& gold);
}

