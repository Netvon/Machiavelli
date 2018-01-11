#pragma once
#include "Phase.h"
#include <vector>
#include <memory>
#include "../Game.h"

namespace machiavelli 
{
	class Phase;

	class State : public std::enable_shared_from_this<State>
	{
	public:
		std::shared_ptr<State> getptr() {
			return shared_from_this();
		}

		template<typename TPhase, typename ...TArgs>
		void add_phase(const std::string& with_name, TArgs&&... arguments) 
		{
			phases.push_back(std::make_shared<TPhase>(with_name, std::shared_ptr<State>(this), std::forward<TArgs>(arguments)...));
		}

		void navigate_to(const std::string& phase_name);

		std::shared_ptr<Phase> current_phase() const;
		Game& game();

		std::shared_ptr<ClientInfo> current_player() const;

		const std::string& last_phase_name() const;

		void handle_input(const Socket & socket, Player& player, const std::string& command);

	private:
		std::vector<std::shared_ptr<Phase>> phases;
		size_t current_location_index;
		std::string _last_phase;

		Game _game;

		bool no_state_set_yet{ true };
	};
}
