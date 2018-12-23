#pragma once
#include "../phases/Option.h"
#include "../phases/Phase.h"
#include <memory>
#include <functional>

namespace machiavelli::actions 
{
	void add_murdered_option(const std::string& key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);
	void add_thief_option(const std::string& key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);
	void add_mage_option(const std::string& key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);
	void add_condottiere_option(const std::string& key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);
	void add_take_option(const std::shared_ptr<machiavelli::Phase> &context, size_t amount, std::function<void(void)> do_after_complete);
	void add_masterbuilder_option(const std::string& key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);

	void add_build_options(std::shared_ptr<Phase> context, std::function<void(void)> do_on_enter_menu, std::function<void(void)> do_after_complete);

	void add_actions_for(const Player::character_card & card, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete);
}

