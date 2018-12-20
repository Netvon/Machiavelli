#include "State.h"

namespace machiavelli
{
	void State::navigate_to(const std::string & phase_name)
	{
		for (auto phase : phases) {

			if (phase->name() == phase_name) {

				if (!no_state_set_yet) {
					_last_phase = current_phase()->name();
				}
				else {
					no_state_set_yet = false;
				}
				current_phase_name = phase_name;

				for (auto player : _game.getPlayers()) {
					current_phase()->entered_phase(player->get_socket(), player->get_player());
				}

				return;
			}
		}
	}

	std::shared_ptr<Phase> State::current_phase() const {
		for (auto phase : phases) {
			if (phase->name() == current_phase_name) {
				return phase;
			}
		}

		return nullptr;
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

	bool State::add_player(std::shared_ptr<ClientInfo> player)
	{
		return _game.addPlayer(player);
	}

	bool State::phase_changed()
	{
		auto result = _phase_changed;
		_phase_changed = false;
		return result;
	}

	void State::broadcast(const std::string & message)
	{
		_game.broadcast(message);
	}

	unsigned int State::getCharacterPosition() const
	{
		return _characterPosition;
	}

	void State::changeCharacterOrder(const unsigned int position)
	{
		if (position > static_cast<unsigned int>(CharacterCard::loaded_amount()))
			_characterPosition = 1;
		else
			_characterPosition = position;
	}
}
