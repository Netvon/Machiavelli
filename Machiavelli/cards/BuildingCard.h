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
		BuildingCard() = default;
		~BuildingCard() = default;

		BuildingCard(const std::string& name, const Gold& cost, CardEffect effect, CardAction action);
		
		BuildingCard& operator=(const BuildingCard& other);
		bool operator==(const BuildingCard& other);

		operator const Gold&() const;

		const Gold& cost() const;
		const std::string& name() const;
		const std::string& description() const;
		const CardCategory& category() const;

		/*void operator () (Game& game);
		void operator () (Player& player);*/

		void setIsBuilt(bool pIsBuilt);
		bool getIsBuilt() const;

	private:
		Gold _cost{ 1_g };
		std::string _name{ "<no name>" };
		std::string _description;
		CardCategory _category{ CardCategory::none() };
		CardEffect _effect;
		CardAction _action;
		bool _isBuilt = false;

		friend std::istream & operator>>(std::istream & os, BuildingCard & card);
	};

	std::istream& operator>>(std::istream& os, BuildingCard& card);

	
}

