#pragma once
#include "Option.h"
#include "State.h"
#include <vector>
#include <memory>

#include "../Player.h"
#include "../network/Socket.h"
#include "../network/ClientCommand.h"

namespace machiavelli {
	class State;
	class Phase
	{
	public:
		Phase(const std::string& name, std::shared_ptr<State> state);
		~Phase();

		void add_option(const std::string& command, const std::string & name, Option::handler func);
		const std::string& name() const;

		void clear_options();

		void virtual print(const Socket & socket, const Player& player) = 0;
		void handle_input(const Socket & socket, Player& player, const std::string& command);

		std::shared_ptr<State> state() const;

		void virtual entered_phase(const Socket & socket, const Player& player) = 0;

		void print_info(const Socket & socket, const Player& player);

	private:
		std::vector<Option> options;
		std::string _name = "<no name>";
		std::shared_ptr<State> _state;

		virtual void handle_option_selected(const Option& option, const Socket & socket, Player& player) {};
	};
}

