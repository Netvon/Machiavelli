#include "BuildingCard.h"
#include <iterator>
#include "..\util\CsvValue.h"

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
		return _name == other._name && _cost == other._cost && _category == other._category;
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

	const std::string & BuildingCard::description() const
	{
		return _description;
	}

	void BuildingCard::operator()(Game & game)
	{
		if(_action) _action(game);
	}

	void BuildingCard::operator()(Player & player)
	{
		if(_effect) _effect(player);
	}

	std::istream & operator>>(std::istream & is, BuildingCard & card)
	{
		std::istream::sentry s(is);
		
		if (s) {
			std::string description_string;
			std::string category_string;
			std::string cost_string;
			std::string name;
			int cost{ 0 };

			std::getline(is, name, ';');
			std::getline(is, cost_string, ';');
			std::getline(is, category_string, ';');
			std::getline(is, description_string, '\n');

			if (!cost_string.empty()) {
				cost = std::stoi(cost_string);
				card._cost = cost;
			}

			if (!description_string.empty()) {
				card._description = description_string;
			}

			if (!category_string.empty()) {
				card._category = CardCategory::with(category_string);
			}

			card._name = name;
		}

		return is;
	}
}
