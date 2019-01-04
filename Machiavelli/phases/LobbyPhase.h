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
		virtual ~LobbyPhase() = default;

		// Inherited via Phase
		void print(const Socket & socket, const Player & player) override;
		void entered_phase(const Socket & socket, const Player & player) override;
		void add_options() override;
	private:
		int amount_in_game{ 0 };
		bool cheat_mode{ false };
		bool test_win{ false };
		bool give_cards{ false };
		bool test_effect{ false };
		bool test_action{ false };
		bool test_draw_one{ false };
		bool do_not_add_extra_money{ false };

		void set_cheat_data();
	};
}
