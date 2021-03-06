#include <SFML/Graphics.hpp>
#include <iostream>
#include "pinball_menu.h"
#include "pinball_game.h"

#define WIDTH 900
#define HEIGHT 1050
#define GAMEWIDTH 900

int main()
{
	// Settings 
	sf::ContextSettings settings;
	// Anti Aliasing Enabled
	settings.antialiasingLevel = 8;

	// sets render window to WIDTH x HEIGHT size and antialiasing is set to make it look pretty
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pinball SetUp", sf::Style::Close | sf::Style::Titlebar, settings);
	window.setFramerateLimit(180);
	//Game State 
	int game_state = 0;
	// while loop only exits when the window is closed
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
                case sf::Event::Closed:
					window.close();
					break;
		}

		// checks the returned value of menu or play_game and moves to the needed gamestate.
		while (game_state != -1)
		{
			switch (game_state)
			{
			case 0: // initial game state
			{
				game_state = menu(&window);
				break;
			}
			case 1:
				// play game
				game_state = play_game(&window);
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				// test case x
				game_state = play_game(&window, game_state - 1);
				break;
			case 7:
			{
				//exit game
				window.close();
				game_state = -1;
			}
			break;
			default:
				game_state = 0; // show menu again
				break;
			}
		}
	}

	return 0;
}
