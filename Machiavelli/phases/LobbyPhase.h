#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class LobbyPhase : public Phase
	{
	public:
		LobbyPhase(const std::string & name, std::shared_ptr<State> state);
		~LobbyPhase();

		// Inherited via Phase
		virtual void print(const Socket & socket, const Player & player) override;
		virtual void entered_phase(const Socket & socket, const Player & player) override;
		virtual void add_options() override;
	private:
		int amount_in_game{ 0 };
		bool cheat_mode{ false };
		bool test_win{ false };
		bool give_cards{ false };

		void set_cheat_data();
	};
}
