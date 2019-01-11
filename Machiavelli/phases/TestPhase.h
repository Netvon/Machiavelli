#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli {
	class TestPhase : public Phase
	{
	private:
		void handle_cool(const Socket& socket, Player& player);
		void handle_hallo(const Socket& socket, Player& player);
		void handle_turn(const Socket& socket, Player& player);

	public:
		TestPhase(const std::string & name, std::shared_ptr<State> state);

		~TestPhase() = default;

		// Inherited via Phase
		void print(const Socket & socket, const Player& player) override;
		void entered_phase(const Socket & socket, const Player & player) override;
		void add_options() override;

		// Inherited via Phase
		virtual void reset() override;
	};
}

