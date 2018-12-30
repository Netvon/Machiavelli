#pragma once
#include "..\network\Socket.h"
#include "..\Player.h"
#include <string>
#include <functional>
#include <utility>
#include "..\data\memleak.h"

namespace machiavelli
{
	class Option {
	public:

		using handler = std::function<void(const Socket&, Player&)>;

		Option() = default;
		Option(std::string command, std::string name, handler function, bool is_for_current_player = false)
			: _command(std::move(command)), _name(std::move(name)), _func(std::move(function)), _for_current_player(is_for_current_player) {};

		const std::string& name() const {
			return _name;
		}

		const std::string& command() const {
			return _command;
		}

		handler function() const {
			return _func;
		}

		bool is_for_current_player() const {
			return _for_current_player;
		}

	private:
		std::string _command = def::NO_COMMAND_SET;
		std::string _name = def::NO_NAME_SET;
		handler _func;
		bool _for_current_player = false;
	};
}

