#pragma once
#include "..\data\memleak.h"
#include "Option.h"
#include "State.h"
#include <vector>
#include <memory>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include "../Player.h"
#include "../network/Socket.h"
#include "../network/ClientCommand.h"

namespace machiavelli {
	class State;
	class Phase
	{
	public:
		Phase(const std::string& name, std::shared_ptr<State> state);
		virtual ~Phase() {
			options.clear();
			_state.reset();
		}

		void remove_option(const std::string& command);
		void add_option(const std::string& command, const std::string & name, Option::handler func, bool is_for_current_player = false);
		const std::string& name() const;

		void clear_options();

		void virtual print(const Socket & socket, const Player& player) = 0;
		void handle_input(const Socket & socket, Player& player, const std::string& command);

		std::shared_ptr<State> state() const;

		void virtual entered_phase(const Socket & socket, const Player& player) = 0;

		void enable_defaults();
		void reset_options(bool enable_defaults = true);
		void print_info(const Socket & socket, const Player& player);
		void print_message(const Socket & socket, const Player& player, const std::string& message);
		
	
	private:
		virtual void add_options() = 0;
		
		void print_cards(const Socket& socket, const Player& player);
		void print_buildings(const Socket& socket, const Player& player);
		void print_gold(const Socket& socket, const Player& player);

		std::vector<Option> options;
		std::string _name = "<no name>";
		std::shared_ptr<State> _state;

		virtual void handle_option_selected(const Option& option, const Socket & socket, Player& player) {};
	};
}

