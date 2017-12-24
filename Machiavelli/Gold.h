#pragma once
#include <ostream>
namespace machiavelli
{
	class Gold
	{
	public:
		typedef unsigned long long int value;

		Gold() = default;
		Gold(value amount);
		~Gold() = default;

		operator value() const;
		operator unsigned int() const;
		operator int() const;
		operator bool() const;

		Gold& operator++();
		Gold& operator--();

		Gold& operator+=(value add);
		Gold& operator-=(value subtract);

		value amount() const;
		void amount(value new_amount);

	private:
		value _amount = 0;
	};

	Gold operator "" g(unsigned long long int amount);
	std::ostream& operator<<(std::ostream& os, const Gold& gold);
	std::istream& operator>>(std::istream& is, Gold& gold);
}