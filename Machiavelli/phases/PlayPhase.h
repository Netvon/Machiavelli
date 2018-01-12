#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class PlayPhase : public Phase
	{
	private:
		void handle_turn(const Socket& socket, const Player& player);
		void nextTurn(const Socket& socket, const Player& player);
	public:
		PlayPhase(const std::string & name, std::shared_ptr<State> state);
		~PlayPhase();

		// Inherited via Phase
		virtual void print(const Socket & socket, const Player& player) override;
		virtual void entered_phase(const Socket & socket, const Player & player) override;
		virtual void add_options() override;
	};
}
