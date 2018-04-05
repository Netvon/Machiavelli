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

		/*operator value() const;
		operator unsigned int() const;
		*/
		/*operator bool() const;*/
		operator int() const;

		Gold& operator=(const Gold& other);

		Gold& operator++();
		Gold& operator--();

		Gold& operator+=(value add);
		Gold& operator-=(value subtract);

		value amount() const;
		void amount(value new_amount);

	private:
		value _amount = 0;
	};

	Gold operator "" _g(unsigned long long int amount);
	std::ostream& operator<<(std::ostream& os, const Gold& gold);
}