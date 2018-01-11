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
	public:
		GamePhase(const std::string & name, std::shared_ptr<State> state);
		~GamePhase();

		// Inherited via Phase
		virtual void print(const Socket & socket, const Player& player) override;
		virtual void entered_phase(const Socket & socket, const Player & player) override;
		virtual void add_options() override;
	};
}
