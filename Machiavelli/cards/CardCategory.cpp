#include "CardCategory.h"

namespace machiavelli
{
	const CardCategory & CardCategory::none()
	{
		static CardCategory instance;
		return instance;
	}

	const CardCategory & CardCategory::yellow()
	{
		static CardCategory instance{ "geel" };
		return instance;
	}

	const CardCategory & CardCategory::green()
	{
		static CardCategory instance{ "groen" };
		return instance;
	}

	const CardCategory & CardCategory::blue()
	{
		static CardCategory instance{ "blauw" };
		return instance;
	}

	const CardCategory & CardCategory::purple()
	{
		static CardCategory instance{ "lila" };
		return instance;
	}

	const CardCategory & CardCategory::red()
	{
		static CardCategory instance{ "rood" };
		return instance;
	}

	bool CardCategory::operator==(const CardCategory & other) const
	{
		if (other.empty())
			return false;

		return this->_name == other._name;
	}

	bool CardCategory::operator!=(const CardCategory & other) const
	{
		return !((*this) == other);
	}

	CardCategory::CardCategory(const std::string & name)
		: _name{ name }
	{

	}

	const std::string & CardCategory::name() const
	{
		return _name;
	}

	bool CardCategory::empty() const
	{
		return _name.empty();
	}
}
