#include "Effects.h"
#include <algorithm>

namespace machiavelli::effects
{
	CardEffect KingCardEffect() {
		return [](machiavelli::Player& player)
		{
			AddGoldForCardCategory(player, CardCategory::yellow());
		};
	}

	CardEffect PreacherCardEffect() {
		return [](machiavelli::Player& player)
		{
			AddGoldForCardCategory(player, CardCategory::blue());
		};
	}

	CardEffect MerchantCardEffect() {
		return [](machiavelli::Player& player)
		{
			player.gold() += 1_g;

			AddGoldForCardCategory(player, CardCategory::green());
		};
	}

	CardEffect ArchitectCardEffect() {
		return [](machiavelli::Player& player)
		{
			player.draw_per_turn(4);
			player.build_per_turn(3);
		};
	}

	CardEffect CondottiereCardEffect()
	{
		return [](machiavelli::Player& player)
		{
			AddGoldForCardCategory(player, CardCategory::red());
		};
	}

	void AddGoldForCardCategory(machiavelli::Player & player, machiavelli::CardCategory cat, Gold amount_per_building)
	{
		auto buildings = player.built_buildings();
		auto count = std::count_if(buildings.cbegin(), buildings.cend(), [cat](const BuildingCard& card) {
			return card.category() == cat;
		});

		player.gold() += amount_per_building * count;
	}

	CardEffect CardEffectFactory(const std::string & name)
	{
		if (name == characters::KONING) { return KingCardEffect(); }
		if (name == characters::PREDIKER) { return PreacherCardEffect(); }
		if (name == characters::KOOPMAN) { return MerchantCardEffect(); }
		if (name == characters::BOUWMEESTER) { return ArchitectCardEffect(); }
		if (name == characters::CONDOTTIERE) { return CondottiereCardEffect(); }

		return CardEffect();
	}

}
