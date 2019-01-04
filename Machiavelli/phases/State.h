#pragma once
#include "..\data\memleak.h"
#include "Phase.h"
#include <vector>
#include <memory>
#include "../Game.h"

namespace machiavelli 
{
	class Phase;

	class State
		: public std::enable_shared_from_this<State>
	{
	public:

		template<typename TPhase, typename ...TArgs>
		void add_phase(const std::string& with_name, TArgs&&... arguments) 
		{
			auto shared = std::make_shared<TPhase>(with_name, shared_from_this(), std::forward<TArgs>(arguments)...);
			phases.push_back(shared);
		}

		void navigate_to(const std::string& phase_name);
		bool has_phase(const std::string& phase_name) const;

		std::shared_ptr<Phase> current_phase() const;
		Game& game();

		std::shared_ptr<ClientInfo> current_player() const;

		const std::string& last_phase_name() const;

		void handle_input(const Socket & socket, Player& player, const std::string& command);

		bool add_player(std::shared_ptr<ClientInfo> player);

		bool phase_changed();

		void broadcast(const std::string & message);
		
		unsigned int getCharacterPosition() const;
		void changeCharacterOrder(unsigned int position);

	private:
		std::vector<std::shared_ptr<Phase>> phases;
		std::string current_phase_name;
		unsigned int _characterPosition = 1;
		std::string _last_phase;

		Game _game;

		bool no_state_set_yet{ true };

		bool _phase_changed{ false };
	};
}
