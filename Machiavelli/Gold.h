#pragma once
#include <ostream>
namespace machiavelli
{
	class Gold
	{
	public:
		using value = unsigned long long int;

		Gold(value amount);
		Gold() = default;
		virtual ~Gold() = default;

		Gold(const Gold& other);
		Gold(Gold&& val);

		/*operator value() const;
		operator unsigned int() const;
		*/
		/*operator bool() const;*/
		operator int() const;

		Gold& operator=(const Gold& other);
		Gold& operator=(Gold&& val);
		Gold& operator=(value&& val);

		Gold& operator++();
		Gold& operator--();

		Gold& operator+=(value add);
		Gold& operator-=(value subtract);

		value amount() const;
		void amount(value new_amount);

	private:
		value _amount{ 0 };
	};

	Gold operator "" _g(unsigned long long int amount);
	std::ostream& operator<<(std::ostream& os, const Gold& gold);
}