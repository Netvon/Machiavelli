#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class EndPhase : public Phase
	{
	private:
		void handle_turn(const Socket& socket, const Player& player);
		void nextTurn(const Socket& socket, const Player& player);

		int player1Score{ -1 };
		int player2Score{ -1 };

		int in_phase{ 0 };
	public:
		EndPhase(const std::string & name, std::shared_ptr<State> state);

		void countPoints(const Socket & socket, const Player & player);

		// Inherited via Phase
		void print(const Socket & socket, const Player& player) override;
		void entered_phase(const Socket & socket, const Player & player) override;
		void add_options() override;

		// Inherited via Phase
		virtual void reset() override;
	};
}