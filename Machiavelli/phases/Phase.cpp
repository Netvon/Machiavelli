#include "Phase.h"

namespace machiavelli
{
	Phase::Phase(const std::string & name, std::shared_ptr<State> state)
		: _name(name), _state(state)
	{
	}

	Phase::~Phase()
	{
	}

	void Phase::add_option(const std::string& command, const std::string & name, Option::handler func)
	{
		options.push_back(Option(command, name, func));
	}

	const std::string & Phase::name() const
	{
		return _name;
	}

	void Phase::clear_options()
	{
		options.clear();
	}

	void Phase::handle_input(const Socket & socket, Player& player, const std::string& command)
	{
		if (command.empty()) {
			return;
		}

		bool found_match = false;

		for (auto& option : options) {
			if (option.command() == command) {
				found_match = true;

				option.function()(socket, player);
				handle_option_selected(option, socket, player);
			}
		}

		if(!found_match)
			socket << "Unknown command: " << command << "\n";
	}
	inline std::shared_ptr<State> Phase::state() const {
		return _state;
	}
}
