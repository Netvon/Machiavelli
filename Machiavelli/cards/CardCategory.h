#pragma once
#include <string>
namespace machiavelli
{
	class CardCategory
	{
	public:
		static const CardCategory& none();
		static const CardCategory& yellow();
		static const CardCategory& green();
		static const CardCategory& blue();
		static const CardCategory& purple();
		static const CardCategory& red();
		static const CardCategory& with(const std::string& name);
		static const int total_amount();

		bool operator==(const CardCategory& other) const;
		bool operator!=(const CardCategory& other) const;
		bool operator<(const CardCategory& other) const;

		CardCategory() = default;
		CardCategory(const std::string& name);
		const std::string& name() const;
		bool empty() const;
	private:
		std::string _name;
	};
}
