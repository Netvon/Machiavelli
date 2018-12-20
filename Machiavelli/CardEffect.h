#pragma once
#include <functional>
namespace machiavelli
{
	class Player;
	class Game;

	using CardEffect = std::function<void(machiavelli::Player&)>;
	using CardAction = std::function<void(machiavelli::Game&, machiavelli::Player&)>;

}