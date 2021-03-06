#include "Gold.h"

namespace machiavelli 
{
	Gold::Gold(Gold::value amount)
	{
		this->_amount = amount;
	}

	Gold::Gold(const Gold & other)
		: _amount{ other._amount }
	{
	}

	Gold::Gold(Gold && val)
		: _amount{std::move(val._amount)}
	{

	}

	/*Gold::operator bool() const
	{
		return _amount > 0;
	}*/

	Gold::operator int() const
	{
		return static_cast<int>(_amount);
	}

	Gold & Gold::operator=(const Gold & other)
	{
		_amount = other._amount;
		return *this;
	}

	Gold & Gold::operator=(Gold && val)
	{
		_amount = std::move(val._amount);
		return *this;
	}

	Gold & Gold::operator=(value && val)
	{
		_amount = std::move(val);
		return *this;
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

	Gold operator""_g(unsigned long long int amount)
	{
		return machiavelli::Gold{ amount };
	}

	std::ostream & operator<<(std::ostream & os, const Gold & gold)
	{
		std::ostream::sentry s(os);
		if (s) {
			os << gold.amount();
		}

		return os;
	}
}