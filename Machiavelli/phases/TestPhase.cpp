#include "TestPhase.h"
using namespace std::placeholders;

namespace machiavelli 
{

	TestPhase::TestPhase(const std::string & name, std::shared_ptr<State> state)
		: Phase(name, state)
	{
		add_option("be cool", "be cool command", std::bind(&TestPhase::handle_cool, this, _1, _2));
		add_option("hallo", "hallo command", std::bind(&TestPhase::handle_hallo, this, _1, _2));
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
		socket << "Cool! " << player.name() << "\n";
	}

	void TestPhase::handle_hallo(const Socket & socket, Player & player)
	{
		socket << "Hallo! " << player.name() << "\n";
	}
}
