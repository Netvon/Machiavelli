#include "BuildingCard.h"
#include <iterator>

namespace machiavelli
{
	BuildingCard::BuildingCard(const std::string & name, const Gold & cost, CardEffect effect, CardAction action)
		:_cost{ cost }, _name{ name }, _effect{ effect }, _action{ action }
	{
	}

	BuildingCard & BuildingCard::operator=(const BuildingCard & other)
	{
		_cost = other._cost;
		_name = other._name;
		_category = other._category;
		_description = other._description;

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

	std::string BuildingCard::all_info() const
	{
		return name() + " - " + category().name() + " ( " + std::to_string(cost().amount()) + " gold )";
	}

	const CardCategory & BuildingCard::category() const
	{
		return _category;
	}

	/*void BuildingCard::operator()(Game & game)
	{
		if (_action) _action(game);
	}

	void BuildingCard::operator()(Player & player)
	{
		if (_effect) _effect(player);
	}*/

	void BuildingCard::setIsBuilt(bool pIsBuilt)
	{
		_isBuilt = pIsBuilt;
	}

	bool BuildingCard::getIsBuilt() const
	{
		return _isBuilt;
	}

	bool BuildingCard::is_empty() const
	{
		return _name == def::NO_NAME_SET;
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

			if (!name.empty() && !cost_string.empty() && !category_string.empty()) {

				try
				{
					cost = std::stoi(cost_string);
				}
				catch (const std::exception&)
				{
					is.setstate(is.badbit);
					return is;
				}

				card._cost = cost;
				card._description = description_string;
				card._category = CardCategory(category_string);
				card._name = name;

				is.setstate(is.goodbit);
			}
			else {
				is.setstate(is.badbit);
			}
		}

		return is;
	}
}
