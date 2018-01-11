#include "State.h"

namespace machiavelli
{
	void State::navigate_to(const std::string & phase_name)
	{
		size_t index = 0;
		for (auto phase : phases) {

			if (phase->name() == phase_name) {

				if (!no_state_set_yet) {
					_last_phase = current_phase()->name();
				}
				else {
					no_state_set_yet = false;
				}

				current_location_index = index;
				return;
			}
			else {
				index++;
			}
		}
	}

	std::shared_ptr<Phase> State::current_phase() const {
		return phases.at(current_location_index);
	}

	Game & State::game()
	{
		return _game;
	}

	std::shared_ptr<ClientInfo> State::current_player() const
	{
		return _game.current_player();
	}

	const std::string & State::last_phase_name() const
	{
		return _last_phase;
	}

	void State::handle_input(const Socket & socket, Player & player, const std::string & command)
	{
		current_phase()->handle_input(socket, player, command);
	}
}
