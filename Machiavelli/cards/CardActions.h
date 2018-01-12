#pragma once
#include "../phases/Option.h"
#include "../phases/Phase.h"
#include <memory>

namespace machiavelli::actions 
{
	void add_murdered_option(const std::string& key, std::shared_ptr<Phase> context);
	void add_thief_option(const std::string& key, std::shared_ptr<Phase> context);
	void add_mage_option(const std::string& key, std::shared_ptr<Phase> context);
	void add_take_option(const std::shared_ptr<machiavelli::Phase> &context, const size_t &i);

	void add_build_options(std::shared_ptr<Phase> context);
}

