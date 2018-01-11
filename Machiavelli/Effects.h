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

	CardEffect CardEffectFactory(const std::string& name);
}

