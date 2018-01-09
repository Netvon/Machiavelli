#pragma once
#include <functional>
namespace machiavelli
{
	class Player;
	class Game;

	typedef std::function<void(machiavelli::Player&)> CardEffect;
	typedef std::function<void(machiavelli::Game&)> CardAction;


}