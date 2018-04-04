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
	public:
		EndPhase(const std::string & name, std::shared_ptr<State> state);
		~EndPhase();

		void countPoints(const Socket & socket, const Player & player);

		// Inherited via Phase
		virtual void print(const Socket & socket, const Player& player) override;
		virtual void entered_phase(const Socket & socket, const Player & player) override;
		virtual void add_options() override;
	};
}