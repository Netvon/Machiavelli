#include "Effects.h"

namespace machiavelli::effects
{
	CardEffect KingCardEffect() {
		return [](machiavelli::Player& player)
		{
			for (auto& card : player.built_buildings()) {
				if (card.category() == CardCategory::yellow()) {
					player.gold() += 1_g;
				}
			}

		};
	}

	CardEffect PreacherCardEffect() {
		return [](machiavelli::Player& player)
		{
			for (auto& card : player.built_buildings()) {
				if (card.category() == CardCategory::blue()) {
					player.gold() += 1_g;
				}
			}
		};
	}

	CardEffect MerchantCardEffect() {
		return [](machiavelli::Player& player)
		{
			player.gold() += 1_g;

			for (auto& card : player.built_buildings()) {
				if (card.category() == CardCategory::green()) {
					player.gold() += 1_g;
				}
			}
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
			for (auto& card : player.built_buildings()) {
				if (card.category() == CardCategory::red()) {
					player.gold() += 1_g;
				}
			}
		};
	}

	CardEffect CardEffectFactory(const std::string & name)
	{
		if (name == "Koning") return KingCardEffect();
		if (name == "Prediker") return PreacherCardEffect();
		if (name == "Koopman") return MerchantCardEffect();
		if (name == "Bouwmeester") return ArchitectCardEffect();
		if (name == "Condottiere") return CondottiereCardEffect();

		return CardEffect();
	}

}
