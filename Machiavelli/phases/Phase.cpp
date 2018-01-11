#include "Phase.h"

namespace machiavelli
{
	Phase::Phase(const std::string & name, std::shared_ptr<State> state)
		: _name(name), _state(state)
	{
		using namespace std::placeholders;

		add_option("info", "show this info", std::bind(&Phase::print_info, this, _1, _2));
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
			socket << "Unknown command: " << command << "\nTry the 'info' command to see a list of all commands.\n";
	}

	std::shared_ptr<State> Phase::state() const {
		return _state;
	}

	void Phase::enable_defaults()
	{
		using namespace std::placeholders;

		add_option("cards", "show your cards", std::bind(&Phase::print_cards, this, _1, _2));
		add_option("building", "show your buildings", std::bind(&Phase::print_buildings, this, _1, _2));
		add_option("gold", "show your gold", std::bind(&Phase::print_gold, this, _1, _2));
	}

	void Phase::print_info(const Socket & socket, const Player & player)
	{
		socket << "========= Info =========\nCurrent State: " << state()->current_phase()->name()  << " | Name: " << player.name() << " | Gold: " << player.gold() << "\n";

		socket << "----------\n";
		socket << "Commands;\n";

		for (auto& option : options) {
			socket << " - " << option.command() << "\n   Name: " << option.name() << "\n";
		}

		socket << "----------\n";
	}

	void Phase::print_cards(const Socket & socket, const Player & player)
	{
		socket << "========= Your Cards =========\n";
		socket << "<cards here>\n";
	}

	void Phase::print_buildings(const Socket & socket, const Player & player)
	{
		socket << "========= Your Cards =========\n";
		socket << "<buildings here>\n";
	}

	void Phase::print_gold(const Socket & socket, const Player & player)
	{
		socket << "========= Gold =========\n";
		socket << player.gold() << "\n";
	}
}
