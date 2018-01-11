#include "TestPhase.h"
using namespace std::placeholders;

namespace machiavelli 
{

	TestPhase::TestPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_option("be cool", "be cool command", std::bind(&TestPhase::handle_cool, this, _1, _2));
		add_option("hallo", "hallo command", std::bind(&TestPhase::handle_hallo, this, _1, _2));
		add_option("turn", "turn command", std::bind(&TestPhase::handle_turn, this, _1, _2));
	}

	TestPhase::~TestPhase()
	{

	}

	void TestPhase::print(const Socket & socket, const Player& player)
	{
		socket << "Now in: TestPhase\nName:\t" << player.name() <<  "\tGold:\t" << player.gold() << "\n";
	}

	void TestPhase::entered_phase(const Socket & socket, const Player & player)
	{

	}

	void TestPhase::handle_cool(const Socket & socket, Player & player)
	{
		socket << "Cool! " << player.name() << "\r\n";

		add_option("1", "be cool command", [=](const auto& a, auto& b) {
			a << "pressed 1";

			reset_options();
		});

		add_option("2", "be cool command", [=](const auto& a, auto& b) {
			a << "pressed 2";

			reset_options();
		});

		add_option("3", "be cool command", [=](const auto& a, auto& b) {
			a << "pressed 3";

			reset_options();
		});

		socket << "\r\n";

		print_info(socket, player);
	}

	void TestPhase::handle_hallo(const Socket & socket, Player & player)
	{
		socket << "Hallo! " << player.name() << "\n";
	}

	void TestPhase::handle_turn(const Socket & socket, Player & player)
	{
		auto& game = state()->game();
		auto& p = player;

		game.setKing();

		game.giveAmountOfBuildingCardsToPlayer(player, 4);

		socket << "\n\r";

		socket << "Goud:" << p.gold() << "\n\r";

		socket << "\n\r";

		socket << "Gebouwen:" << "\n\r";

		for (auto& card : p.getPlayerBuildingCards()) {
			if (card.getIsBuilt()) {
				if (card.description().empty()) {
					socket << card.name() << " (" << card.category().name() << ", " << card.cost() << ")\n\r";
				}
				else {
					socket << card.name() << " (" << card.category().name() << ", " << card.cost() << ", " << card.description() << ")\n\r";
				}
			}
		}

		socket << "\n\r";

		socket << "Handkaarten:" << "\n\r";
		for (auto& card : p.getPlayerBuildingCards()) {
			if (!card.getIsBuilt()) {
				if (card.description().empty()) {
					socket << card.name() << " (" << card.category().name() << ", " << card.cost() << ")\n\r";
				}
				else {
					socket << card.name() << " (" << card.category().name() << ", " << card.cost() << ", " << card.description() << ")\n\r";
				}
			}
		}

		if (p == game.getKing()) {

		}
	}
}
