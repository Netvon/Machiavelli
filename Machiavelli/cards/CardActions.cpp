#include "CardActions.h"
#include "../phases/Phase.h"

namespace machiavelli::actions
{
	void add_murdered_option(const std::string & key, std::shared_ptr<Phase> context)
	{
		context->add_option(key, "Murder a Character", [&, context](const Socket& s, Player& p) 
		{
			context->reset_options(true);

			auto& game = context->state()->game();

			auto cards = game.drawn_character_card(p, "Moordenaar");

			int index = 1;

			for (auto& kv : cards) {
				context->add_option(std::to_string(index), kv.second.name(), [&, context, kv](const Socket& s2, Player& p2)
				{
					auto & player = game.getPlayerByName(kv.first);
					player.kill_character(kv.second.name());

					context->reset_options(true);

				}, true);

				index++;
			}

			context->print_info(s, p);
		}, true);
	}

	void add_thief_option(const std::string & key, std::shared_ptr<Phase> context)
	{
		context->add_option(key, "Steal gold from the other player", [&, context](const Socket& s, Player& p)
		{
			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			auto gold = other_player.gold();
			p.gold() += gold;
			other_player.gold() -= gold;

			context->print_info(s, p);
		}, true);
	}

	void add_mage_option(const std::string & key, std::shared_ptr<Phase> context)
	{
		context->add_option(key + "a", "Switch building cards with other player", [&, context](const Socket& s, Player& p)
		{
			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			other_player.swap_building_cards(p);

			context->print_info(s, p);
		}, true );

		context->add_option(key + "b", "Take new cards", [&, context](const Socket& s, Player& p)
		{
			context->reset_options(true);

			for (size_t i = 1llu; i < p.building_card_amount(); i++)
			{
				add_take_option(context, i);
			}

			context->print_info(s, p);
		}, true);
	}

	void add_condottiere_option(const std::string & key, std::shared_ptr<Phase> context)
	{
		context->add_option(key, "Destroy a building", [&, context](const Socket& s, Player& p) {

			context->reset_options(true);

			auto& game = context->state()->game();
			auto& other_player = game.get_other_player(p);

			int index = 0;

			for (const auto& building : other_player.built_buildings()) {

				context->add_option(std::to_string(index), building.name(), [&, context](const Socket& s2, Player& p2)
				{
					context->reset_options(true);

					p2.gold() -= building.cost() - 1_g;
					p2.destroy_building(building.name());

					p2.discardBuildingCardFromDeck(building);


				}, true);

			}

		}, true);
	}

	void add_take_option(const std::shared_ptr<machiavelli::Phase> &context, const size_t &i)
	{
		context->add_option(std::to_string(i), "Take " + std::to_string(i) + " new cards", [&, context](const Socket& s2, Player& p2) {

			auto& game = context->state()->game();

			size_t count_down = i;

			while (count_down > 0) {
				count_down--;

				game.discard_card(std::move(p2.drawFromBuildingDeck()));
			}

			auto new_cards = game.drawAmountOfBuildingCards(static_cast<int>(i));

			for (auto& card : new_cards) {
				p2.addBuildingCardToDeck(card);
			}

			context->reset_options(true);

		}, true);
	}

	void add_build_options(std::shared_ptr<Phase> context)
	{
		context->add_option("build", "Build a card", [&, context](const Socket& s2, Player& p2) {

			context->reset_options(true);

			int can_build = p2.build_per_turn();
			int index = 0;

			for (const auto& bc : p2.getPlayerBuildingCards()) {
				if (!bc.getIsBuilt()) {

					context->add_option(std::to_string(index), bc.name(), [&, context, bc](const Socket& s, Player& p)
					{
						p.built_building(bc);
						can_build--;
						
						if (can_build > 0)
							context->remove_option(std::to_string(index));
						else
							context->reset_options(true);

					}, true);

					index++;
				}
			}

		}, true);
	}

	void add_actions_for(const Player::character_card & card, std::shared_ptr<Phase> context)
	{
		if (card.name() == "Moordenaar") add_murdered_option("murderer", context);
		if (card.name() == "Dief") add_thief_option("thief", context);
		if (card.name() == "Magi�r") add_mage_option("mage", context);
		if (card.name() == "Condottiere") add_condottiere_option("condottiere", context);
	}
}
