#pragma once
#include "Phase.h"

#include <string>
#include <functional>
#include <memory>

namespace machiavelli
{
	class TurnPhase 
		: public Phase
	{
	private:
		void handle_get_gold(const Socket& socket, Player& player);
		void handle_take_buildingcards(const Socket& socket, Player& player);

		void nextTurn(const Socket& socket, const Player& player);

		bool gotGold = false;
		bool builtBuilding = false;
		bool takenBuildingCards = false;
		bool usedCharacterAction = false;
		bool discardedBuildingCard = false;


		bool takingBuildingCardsNow = false;
		bool usingCharacterAction = false;
		bool buildingBuilding = false;

		bool newTurn = true;

		void check_next_turn();
	public:
		TurnPhase(const std::string & name, std::shared_ptr<State> state);
		~TurnPhase() = default;

		// Inherited via Phase
		void print(const Socket & socket, const Player& player) override;
		void entered_phase(const Socket & socket, const Player & player) override;
		void add_options() override;
	};
}
