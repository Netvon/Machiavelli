#include "Phase.h"

namespace machiavelli
{
	Phase::Phase(const std::string & name, std::shared_ptr<State> state)
		: _name(name), _state(state)
	{
		using namespace std::placeholders;

		add_option("info", "show this info", std::bind(&Phase::print_info, this, _1, _2));
	}

	void Phase::remove_option(const std::string & command)
	{
		options.erase(std::remove_if(options.begin(), options.end(), [command](const Option& o) {
			return o.command() == command;
		}));
	}

	void Phase::add_option(const std::string& command, const std::string & name, Option::handler func, bool is_for_current_player)
	{
		options.emplace_back(Option(command, name, func, is_for_current_player));
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
		bool is_current_player = state()->current_player()->get_player() == player;

		if (command.empty()) {
			return;
		}

		bool found_match = false;

		auto temp_clone = std::vector<Option>(options);

		for (auto& option : temp_clone) {
			if (option.is_for_current_player() && !is_current_player) {
				continue;
			}

			if (option.command() == command ) {
				found_match = true;

				option.function()(socket, player);
				handle_option_selected(option, socket, player);
				return;
			}
		}

		if (!found_match) {
			socket << "Unknown command: " << command << "\nTry the 'info' command to see a list of all commands.\n";
		}
	}

	std::shared_ptr<State> Phase::state() const {
		return _state;
	}

	void Phase::enable_defaults()
	{
		using namespace std::placeholders;

		add_option("cards", "show your cards", std::bind(&Phase::print_cards, this, _1, _2));
		add_option("buildings", "show your buildings", std::bind(&Phase::print_buildings, this, _1, _2));
		add_option("gold", "show your gold", std::bind(&Phase::print_gold, this, _1, _2));
	}

	void Phase::reset_options(bool enable_defaults)
	{
		using namespace std::placeholders;
		options.clear();

		add_option("info", "show this info", std::bind(&Phase::print_info, this, _1, _2));

		if (enable_defaults) {
			this->enable_defaults();
		}

		add_options();
	}

	void Phase::print_info(const Socket & socket, const Player & player)
	{
		bool is_current_player = state()->current_player()->get_player() == player;

		socket << "========= Info =========\r\nCurrent State: " << state()->current_phase()->name()  
			<< " | Name: " << player.name() << " | Gold: " << player.gold() << " | Turn: " << std::to_string(state()->turn_count()) << "\r\n" ;

		if (is_current_player) {
			socket << "\r\n|> it's your turn\r\n";
		}

		socket << "----------\r\n";
		socket << "Commands;\r\n";

		auto result = std::max_element(options.begin(), options.end(), [](const Option& a, const Option& b) {
			return a.command().size() < b.command().size();
		});

		std::ostringstream commands;

		for (auto& option : options) {
			if (option.is_for_current_player() && !is_current_player) {
				continue;
			}

			commands << " [ " << std::setw(result->command().size()) << option.command() << " ] " << option.name() << "\r\n";
		}

		socket << commands.str();

		socket << "----------\r\n";
	}

	void Phase::print_message(const Socket & socket, const Player & player, const std::string & message)
	{

	}

	void Phase::print_cards(const Socket & socket, const Player & player)
	{
		socket << "========= Your Cards =========\n";
		socket << "\r\n";

		for (auto& card : player.getPlayerBuildingCards()) {
			if (!card.getIsBuilt()) {
					
				socket << card.all_info();

				if (!card.description().empty()) {
					socket << " - " << card.description() << "\r\n";
				}

				socket << "\r\n";
			}
		}

		for (auto& card : player.getPlayerCharacterCards()) {
			socket << "#" << card.getOrder() << ". " << card.name() << " - " << card.category().name();
			if (card.is_murdered()) {
				socket << " [ has been murdered ]";
			}

			socket << "\r\n";
		}
	}

	void Phase::print_buildings(const Socket & socket, const Player & player)
	{
		socket << "========= Your Buildings =========\n";
		socket << "\r\n";

		for (auto& card : player.getPlayerBuildingCards()) {
			if (card.getIsBuilt()) {
				socket << card.all_info();

				if (!card.description().empty()) {
					socket << " - " << card.description() << "\r\n";
				}

				socket << "\r\n";
			}
		}
	}

	void Phase::print_gold(const Socket & socket, const Player & player)
	{
		socket << "========= Gold =========\n";
		socket << player.gold() << "\n";
	}
}
