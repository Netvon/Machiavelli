#include "Effects.h"

namespace machiavelli::effects
{
	CardEffect KingCardEffect() {
		return [](machiavelli::Player& player)
		{
			for (auto& card : player.getPlayerBuildingCards()) {
				if (card.category() == CardCategory::yellow()) {
					player.gold() += 1_g;
				}
			}

		};
	}

	CardEffect PreacherCardEffect() {
		return [](machiavelli::Player& player)
		{
			for (auto& card : player.getPlayerBuildingCards()) {
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

			for (auto& card : player.getPlayerBuildingCards()) {
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
		};
	}

	CardEffect CondottiereCardEffect()
	{
		return [](machiavelli::Player& player)
		{
			for (auto& card : player.getPlayerBuildingCards()) {
				if (card.category() == CardCategory::red()) {
					player.gold() += 1_g;
				}
			}
		};
	}

}
