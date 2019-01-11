#pragma once
#include ".\CardEffect.h"
#include "Player.h"
namespace machiavelli::effects
{
	CardEffect KingCardEffect();
	CardEffect PreacherCardEffect();
	CardEffect MerchantCardEffect();
	CardEffect ArchitectCardEffect();
	CardEffect CondottiereCardEffect();

	void AddGoldForCardCategory(machiavelli::Player & player, machiavelli::CardCategory cat, Gold amount_per_building = 1_g);

	CardEffect CardEffectFactory(const std::string& name);
}

