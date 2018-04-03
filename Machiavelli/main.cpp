//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Revised by Jeroen de Haas on 22/11/2016
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "data\memleak.h"
#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <chrono>

#include ".\network\Socket.h"
#include ".\network\Sync_queue.h"
#include ".\network\ClientCommand.h"
#include "Player.h"
#include ".\network\ClientInfo.h"
#include "Game.h"
#include ".\phases\State.h"
#include ".\data\Assets.h"
#include <iterator>
#include <fstream>
#include "phases/TestPhase.h"
#include "phases/GamePhase.h"
#include "phases/PlayPhase.h"
#include "phases/TurnPhase.h"
#include "phases/EndPhase.h"
#include "main.h"
#include "phases/LobbyPhase.h"

namespace machiavelli {
	const int tcp_port{ 1080 };
	const std::string prompt{ "machiavelli> " };
}

static bool running = true;

static Sync_queue<ClientCommand> queue;

static std::shared_ptr<machiavelli::State> state = std::make_shared<machiavelli::State>();

void consume_command() // runs in its own thread
{
	try {
		while (running) {
			ClientCommand command{ queue.get() }; // will block here unless there are still command objects in the queue
			if (auto clientInfo = command.get_client_info().lock()) {
				auto &client = clientInfo->get_socket();
				auto &player = clientInfo->get_player();

				try
				{
					state->handle_input(client, player, command.get_cmd());
					client << "\r\n" << machiavelli::prompt;
				}
				catch (const std::exception& ex) {
					std::cerr << "*** exception in consumer thread for player " << player.name() << ": " << ex.what() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
				catch (...) {
					std::cerr << "*** exception in consumer thread for player " << player.name() << '\n';
					if (client.is_open()) {
						client.write("Sorry, something went wrong during handling of your request.\r\n");
					}
				}
				

				//try {
				//	// TODO handle command here
				//	client << player.name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
				//}
				//catch (const std::exception& ex) {
				//	std::cerr << "*** exception in consumer thread for player " << player.name() << ": " << ex.what() << '\n';
				//	if (client.is_open()) {
				//		client.write("Sorry, something went wrong during handling of your request.\r\n");
				//	}
				//}
				//catch (...) {
				//	std::cerr << "*** exception in consumer thread for player " << player.name() << '\n';
				//	if (client.is_open()) {
				//		client.write("Sorry, something went wrong during handling of your request.\r\n");
				//	}
				//}
			}
		}
	}
	catch (...) {
		std::cerr << "consume_command crashed\n";
	}
}

std::shared_ptr<ClientInfo> init_client_session(Socket client) {
	client.write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
	client.write("What's your name?\r\n");
	client.write(machiavelli::prompt);
	std::string name;
	bool done{ false };
	while (!done) {
		done = client.readline([&name](std::string input) {
			name = input;
		});
	}
	return std::make_shared<ClientInfo>(std::move(client), Player{ name });
}

void handle_client(Socket client) // this function runs in a separate thread
{
	try {
		auto client_info = init_client_session(std::move(client));
		auto &socket = client_info->get_socket();

		if (!state->add_player(client_info)) {
			socket << "Sorry, there are already two players connected. Please try again later.\r\n";
			return;
		}
		
		auto &player = client_info->get_player();
		socket << "Welcome, " << player.name() << ", have fun playing our game!\r\n";

		state->current_phase()->entered_phase(socket, player);

		socket << machiavelli::prompt;

		while (running) { // game loop
			try {

				// read first line of request
				std::string cmd;
				if (socket.readline([&cmd](std::string input) { cmd = input; })) {
					std::cerr << '[' << socket.get_dotted_ip() << " (" << socket.get_socket() << ") " << player.name() << "] " << cmd << "\r\n";

					if (cmd == "quit") {
						socket.write("Bye!\r\n");
						break; // out of game loop, will end this thread and close connection
					}
					else if (cmd == "start") {
						state->add_phase<machiavelli::GamePhase>("game");
						state->add_phase<machiavelli::PlayPhase>("play");
						state->add_phase<machiavelli::TurnPhase>("turn");
						state->add_phase<machiavelli::EndPhase>("end");
						state->navigate_to("game");
						continue;
					}
					else if (cmd == "quit_server") {
						running = false;
					}

					ClientCommand command{ cmd, client_info };
					queue.put(command);
				};

			}
			catch (const std::exception& ex) {
				socket << "ERROR: " << ex.what() << "\r\n";
			}
			catch (...) {
				socket.write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
			}
		}
		// close weg
	}
	catch (std::exception &ex) {
		std::cerr << "handle_client " << ex.what() << "\n";
	}
	catch (...) {
		std::cerr << "handle_client crashed\n";
	}
}

int load_decks(bool &retflag)
{
	retflag = true;
	machiavelli::Deck<machiavelli::BuildingCard> bdeck;
	machiavelli::Deck<machiavelli::CharacterCard> cdeck;

	if (!data::assets::try_load_asset_into("data/Bouwkaarten.csv", bdeck)
		|| !data::assets::try_load_asset_into("data/karakterkaarten.csv", cdeck)) {

		std::cerr << "Failed to load assets.";
		std::cin.get();

		return 0;
	}

	state->game().replace_deck(bdeck);
	state->game().replace_deck(cdeck);
	retflag = false;
	return {};
}

int main(int argc, const char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	state->add_phase<machiavelli::LobbyPhase>("lobby");
	state->navigate_to("lobby");

	bool retflag;
	int retval = load_decks(retflag);
	if (retflag) {
		state.~shared_ptr();
		return retval;
	}

	// start command consumer thread
	std::vector<std::thread> all_threads;
	all_threads.emplace_back(consume_command);

	// create a server socket
	ServerSocket server{ machiavelli::tcp_port };

	try {
		std::cerr << "server listening" << '\n';
		while (running) {
			// wait for connection from client; will create new socket
			server.accept([&all_threads](Socket client) {
				std::cerr << "Connection accepted from " << client.get_dotted_ip() << "\n";
				all_threads.emplace_back(handle_client, std::move(client));
			});
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << ", resuming..." << '\n';
	}
	catch (...) {
		std::cerr << "problems, problems, but: keep calm and carry on!\n";
	}

	for (auto &t : all_threads) {
		t.join();
	}

	state.~shared_ptr();
	return 0;
}

