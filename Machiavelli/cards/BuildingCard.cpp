#include "BuildingCard.h"

namespace machiavelli 
{
	BuildingCard::BuildingCard(const std::string & name, const Gold & cost, CardEffect effect, CardAction action)
		:_cost{ cost }, _name{ name }, _effect{ effect }, _action { action }
	{
	}

	BuildingCard & BuildingCard::operator=(const BuildingCard & other)
	{
		_cost = other._cost;
		_name = other._name;
		_category = other._category;

		return *this;
	}

	bool BuildingCard::operator==(const BuildingCard & other)
	{
		return _name == other._name && _cost == other._cost;
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

	void BuildingCard::operator()(Game & game)
	{
		if(_action) _action(game);
	}

	void BuildingCard::operator()(Player & player)
	{
		if(_effect) _effect(player);
	}

	std::istream & operator>>(std::istream & os, BuildingCard & gold)
	{
		std::istream::sentry s(os);
		
		if (s) {
			std::string name;
			int cost{ 0 };

			os >> name;
			os.ignore(std::numeric_limits<std::streamsize>::max(), ';');
			os >> cost;
		}

		return os;
	}
}
