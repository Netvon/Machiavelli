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
		Option(const std::string& command, const std::string& name, handler function)
			: _command(command), _name(name), _func(function) {};

		const std::string& name() const {
			return _name;
		}

		const std::string command() const {
			return _command;
		}

		handler function() const {
			return _func;
		}

	private:
		std::string _command = 0;
		std::string _name = "<no name>";
		handler _func;
	};
}

