#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class TurnPhase : public Phase
	{
	private:
		void handle_character_turn(const Socket& socket, const Player& player);
		void handle_get_gold(const Socket& socket, const Player& player);
		void handle_take_buildingcards(const Socket& socket, const Player& player);

		void nextTurn(const Socket& socket, const Player& player);

		bool gotGold = false;
		bool builtBuilding = false;
		bool takenBuildingCards = false;
		bool discardedBuildingCard = false;
	public:
		TurnPhase(const std::string & name, std::shared_ptr<State> state);
		~TurnPhase();

		// Inherited via Phase
		virtual void print(const Socket & socket, const Player& player) override;
		virtual void entered_phase(const Socket & socket, const Player & player) override;
		virtual void add_options() override;
	};
}
