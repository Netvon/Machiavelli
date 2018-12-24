#include "CardActions.h"
#include "../phases/Phase.h"

namespace machiavelli::actions
{
	void add_murdered_option(const std::string & key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		context->add_option(key, "Murder a Character", [&, context, do_after_complete](const Socket& s, Player& p)
		{
			context->reset_options(true);

			auto& game = context->state()->game();

			auto cards = game.drawn_character_cards(p, "Moordenaar");

			int index = 1;

			for (auto& kv : cards) {
				context->add_option(std::to_string(index), "Kill " + kv.second.name(), [&, context, kv, do_after_complete](const Socket& s2, Player& p2)
				{
					auto & player = game.getPlayerByName(kv.first)->get_player();
					player.kill_character(kv.second.name());

					s << "You killed '" << kv.second.name() <<"'\n";

					do_after_complete();
					context->reset_options(true);

					context->print_info(s2, p2);

				}, true);

				index++;
			}

			
			context->print_info(s, p);
		}, true);
	}

	void add_thief_option(const std::string & key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		context->add_option(key, "Steal gold from the other player", [&, context, do_after_complete](const Socket& s, Player& p)
		{
			do_after_complete();
			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			if (other_player.gold() > 0) {
				auto gold = other_player.gold();
				p.gold() += gold;
				other_player.gold() -= gold;
			}

			context->print_info(s, p);
		}, true);
	}

	void add_mage_option(const std::string & key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		context->add_option(key + "a", "Switch building cards with other player", [&, context, do_after_complete](const Socket& s, Player& p)
		{
			do_after_complete();
			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			other_player.swap_building_cards(p);

			context->state()->broadcast("Player cards have been switched, type the 'cards' and 'buildings' command to see your new cards and buildings.");

			context->print_info(s, p);
		}, true );

		context->add_option(key + "b", "Take new cards", [&, context, do_after_complete](const Socket& s, Player& p)
		{
			context->reset_options(true);

			for (size_t i = 1llu; i < p.building_card_amount(); i++)
			{
				add_take_option(context, i, do_after_complete);
			}

			context->print_info(s, p);
		}, true);
	}

	void add_condottiere_option(const std::string & key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		context->add_option(key, "Destroy a building", [&, context, do_after_complete](const Socket& s, Player& p) {

			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			if (other_player.built_buildings().size() >= 8) {
				do_after_complete();
				context->reset_options(true);
				return;
			}

			int index = 0;
			int options_added = 0;

			for (const auto& building : other_player.built_buildings()) {

				options_added++;
				context->add_option(std::to_string(index), building.name(), [building, context, &other_player, do_after_complete](const Socket& s2, Player& p2)
				{
					do_after_complete();
					context->reset_options(true);

					p2.gold() -= building.cost() - 1_g;

					other_player.destroy_building(building.name());
					other_player.discardBuildingCardFromDeck(building);

					context->state()->broadcast(p2.name() + " destroyed the other player's '" + building.name() + "' building.");


				}, true);

				index++;
			}

			if (options_added == 0) {
				s << "The other player doesn't have any built Buildings.\n";

				do_after_complete();
				context->reset_options(true);
			}

			context->print_info(s, p);

		}, true);
	}

	void add_take_option(const std::shared_ptr<machiavelli::Phase> &context, size_t amount, std::function<void(void)> do_after_complete)
	{
		auto text = "Take " + std::to_string(amount);
		if (amount == 1) {
			text += " card";
		}
		else {
			text += " cards";
		}

		context->add_option(std::to_string(amount), text, [&, context, do_after_complete, amount](const Socket& s2, Player& p2) {

			do_after_complete();

			auto& game = context->state()->game();

			size_t count_down = amount;

			while (count_down > 0) {
				count_down--;

				game.discard_card(std::move(p2.drawFromBuildingDeck()));
			}

			auto new_cards = game.drawAmountOfBuildingCards(static_cast<int>(amount));

			for (auto& card : new_cards) {
				p2.addBuildingCardToDeck(card);

				s2 << "You got a '" + card.name() + "' card!";
			}

			context->reset_options(true);

		}, true);
	}

	void add_masterbuilder_option(const std::string & key, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		context->add_option(key, "Take 2 building cards", [&, context, do_after_complete](const Socket& s2, Player& p2) {
			auto& game = context->state()->game();
			p2.addBuildingCardToDeck(game.drawBuildingCard());

			do_after_complete();
			context->reset_options(true);
		});
	}

	void add_build_options(std::shared_ptr<Phase> context, std::function<void(void)> do_on_enter_menu, std::function<void(void)> do_after_complete)
	{
		context->add_option("build", "Build a building", [&, context, do_after_complete, do_on_enter_menu](const Socket& s2, Player& p2) {

			do_on_enter_menu();
			context->reset_options(true);

			int can_build = p2.build_per_turn();
			int index = 0;

			for (const auto& bc : p2.getPlayerBuildingCards()) {
				if (!bc.getIsBuilt() && p2.gold() >= bc.cost()) {

					context->add_option(std::to_string(index), bc.name(), [&, context, bc, do_after_complete](const Socket& s, Player& p)
					{
						if (p.gold() >= bc.cost()) {
							p.built_building(bc);
							can_build--;
						}

						bool any_left_to_built = false;

						for (const auto& card : p2.getPlayerBuildingCards()) {
							if (!bc.getIsBuilt() && p2.gold() >= bc.cost()) {
								any_left_to_built = true;
								break;
							}
						}
						
						if (can_build > 0 && p.gold() > 0 && any_left_to_built) {
							context->remove_option(std::to_string(index));
						} else {
							do_after_complete();
							context->reset_options(true);
						}

					}, true);

					index++;
				}
			}

		}, true);
	}

	void add_actions_for(const Player::character_card & card, std::shared_ptr<Phase> context, std::function<void(void)> do_after_complete)
	{
		if (card.name() == "Moordenaar") { add_murdered_option("murderer", context, do_after_complete); }
		if (card.name() == "Dief") { add_thief_option("thief", context, do_after_complete); }
		if (card.name() == "Magiër") { add_mage_option("mage", context, do_after_complete); }
		if (card.name() == "Condottiere") { add_condottiere_option("condottiere", context, do_after_complete); }
		if (card.name() == "Bouwmeester") { add_masterbuilder_option("masterbuilder", context, do_after_complete); }
	}
}
