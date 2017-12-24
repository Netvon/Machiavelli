#include "BuildingCard.h"

namespace machiavelli 
{
	BuildingCard::BuildingCard(const std::string & name, const Gold & cost)
		:_cost{ cost }, _name{ name }
	{
	}

	BuildingCard::operator const Gold&() const
	{
		return _cost;
	}

	const Gold & BuildingCard::cost() const
	{
		return _cost;
	}

	const std::string & BuildingCard::name() const
	{
		return _name;
	}
}
