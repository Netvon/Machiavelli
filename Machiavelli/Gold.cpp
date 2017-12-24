#include "Gold.h"

namespace machiavelli 
{
	Gold::Gold(Gold::value amount)
	{
		this->_amount = amount;
	}

	Gold::operator value() const
	{
		return _amount;
	}

	Gold::operator unsigned int() const
	{
		return static_cast<unsigned int>(_amount);
	}

	Gold::operator int() const
	{
		return static_cast<int>(_amount);
	}

	Gold::operator bool() const
	{
		return _amount > 0;
	}

	Gold & Gold::operator++()
	{
		_amount++;

		return *this;
	}

	Gold & Gold::operator--()
	{
		if (_amount >= 1) {
			_amount--;
		}

		return *this;
	}

	Gold & Gold::operator+=(value add)
	{
		_amount += add;

		return *this;
	}

	Gold & Gold::operator-=(value subtract)
	{
		_amount -= subtract;

		return *this;
	}

	Gold::value Gold::amount() const
	{
		return _amount;
	}

	void Gold::amount(value new_amount)
	{
		_amount = new_amount;
	}

	Gold operator""g(unsigned long long int amount)
	{
		return machiavelli::Gold{ amount };
	}

	std::ostream & operator<<(std::ostream & os, const Gold & gold)
	{
		std::ostream::sentry s(os);
		if (s) {
			os << gold.amount() << "g";
		}

		return os;
	}
}