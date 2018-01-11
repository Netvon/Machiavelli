#pragma once
#include "..\network\Socket.h"
#include "..\Player.h"
#include <string>
#include <functional>

namespace machiavelli
{
	class Option {
	public:

		typedef std::function<void(const Socket&, Player&)> handler;

		Option() {};
		Option(const std::string& command, const std::string& name, handler function, bool is_for_current_player = false)
			: _command(command), _name(name), _func(function), _for_current_player(is_for_current_player) {};

		const std::string& name() const {
			return _name;
		}

		const std::string command() const {
			return _command;
		}

		handler function() const {
			return _func;
		}

		bool is_for_current_player() const {
			return _for_current_player;
		}

	private:
		std::string _command = 0;
		std::string _name = "<no name>";
		handler _func;
		bool _for_current_player = false;
	};
}

