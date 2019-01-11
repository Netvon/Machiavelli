#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class GamePhase : public Phase
	{
	private:
		void handle_character_cards(const Socket& socket, Player& player);
		void nextTurn(const Socket& socket, const Player& player);
		bool characterCardsDrawn = false;
	public:
		GamePhase(const std::string & name, std::shared_ptr<State> state);
		~GamePhase() = default;

		// Inherited via Phase
		void print(const Socket & socket, const Player& player) override;
		void entered_phase(const Socket & socket, const Player & player) override;
		void add_options() override {};

		// Inherited via Phase
		virtual void reset() override;
	};
}
