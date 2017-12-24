#pragma once
#include "..\Gold.h"
#include "CardCategory.h"
#include <string>
namespace machiavelli
{
	class BuildingCard
	{
	public:
		BuildingCard() = default;
		BuildingCard(const std::string& name, const Gold& cost);
		~BuildingCard() = default;

		operator const Gold&() const;

		const Gold& cost() const;
		const std::string& name() const;

	private:
		const Gold _cost{ 1g };
		std::string _name{ "<no name>" };
		const CardCategory _category{ CardCategory::none() };
	};
}

