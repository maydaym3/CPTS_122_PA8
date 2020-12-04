#include <SFML/Graphics.hpp>
#include "ball.h"
#include "flipper.h"
#include "launcher.h"
#include <iostream>
#include "pa8.h"

int main()
{
	sf::ContextSettings settings;
	// Anti Aliasing Enabled
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(900, 900), "Pinball SetUp", sf::Style::Close | sf::Style::Titlebar, settings);

	// Pinball
	ball* pinball = new ball(825, 770);

	//Flippers
	flipper* leftFlipper = new flipper(390, 815, 90, false);
	flipper* rightFlipper = new flipper(700, 815, 90, true);

	//launcher
	launcher* ballLauncher = new launcher(855, 830);

	sf::RectangleShape rectangle(sf::Vector2f(10.f, 750.f));
	rectangle.setFillColor(sf::Color::White);
	rectangle.move(800, 175);
	//rectangle.setPosition(600.f, 175.f);

	sf::RectangleShape left_rectangle(sf::Vector2f(10.f, 715.f));
	left_rectangle.move(280, 0);
	//left_rectangle.setPosition(80.f, 0.f);
	left_rectangle.setFillColor(sf::Color::White);

	//to launch the ball, we need to make this move vertically with options for launch strength
	//that correlate with ball speed


	sf::ConvexShape corner;
	corner.setPointCount(3);
	corner.setPoint(0, sf::Vector2f(900.f, 0.f));
	corner.setPoint(1, sf::Vector2f(900.f, 60.f));
	corner.setPoint(2, sf::Vector2f(840.f, 0.f));

	sf::ConvexShape left_corner;
	left_corner.setPointCount(3);
	left_corner.setPoint(0, sf::Vector2f(290.f, 0.f));
	left_corner.setPoint(1, sf::Vector2f(290.f, 60.f));
	left_corner.setPoint(2, sf::Vector2f(350.f, 0.f));

	sf::RectangleShape left_bound(sf::Vector2f(160.f, 15.f));
	left_bound.setPosition(290.f, 700.f);
	left_bound.rotate(45.f);

	sf::RectangleShape right_bound(sf::Vector2f(160.f, 15.f));
	right_bound.setPosition(810.f, 710.f);
	right_bound.rotate(135.f);

	//adding in the text
	sf::Font MyFont;
	if (!MyFont.loadFromFile("OCR-A BT.ttf"))
	{
		// error...
	}

	sf::Text title; Text titleshadow; Text score; Text scoreshadow;
	title_score_game_setup(&MyFont, &title, &titleshadow, &score, &scoreshadow);
	

	sf::RectangleShape score_box1(sf::Vector2f(170.f, 60.f));
	score_box1.setPosition(55.f, 115.f);
	score_box1.setFillColor(sf::Color::Red);

	sf::RectangleShape score_box2(sf::Vector2f(170.f, 60.f));
	score_box2.setPosition(60.f, 120.f);
	score_box2.setFillColor(sf::Color::Blue);

	//menu boxes
	sf::RectangleShape outerbox(sf::Vector2f(450.f, 750.f));
	sf::RectangleShape start_playable(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape test1(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape test2(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape test3(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape test4(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape test5(sf::Vector2f(350.f, 50.f));
	sf::RectangleShape exit(sf::Vector2f(350.f, 50.f));

	//text boxes for menu
	sf::Text manu_title; Text created_by; Text startplayable; Text testcase1; Text testcase2; Text testcase3; Text testcase4; Text testcase5; Text exitText;
	//text setting
	

	sf::RectangleShape mouse_check(sf::Vector2f(10.f, 10.f));

	//menu initializations
	create_menu(&outerbox, &start_playable, &test1, &test2, &test3, &test4, &test5, &exit);
	create_menu2(&MyFont, &manu_title, &created_by, &startplayable, &testcase1, &testcase2, &testcase3, &testcase4, &testcase5, &exitText);

	int user_choice = 0;
	int count = 0;
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

		// Keyboard Actions
		leftFlipper->rotateFlipper(Keyboard::isKeyPressed(Keyboard::A));
		rightFlipper->rotateFlipper(Keyboard::isKeyPressed(Keyboard::D));
		ballLauncher->moveLauncher(Keyboard::isKeyPressed(Keyboard::Space));

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				//Rotate Right Flipper CW until max rotation
				rightFlipper->rotateFlipper(true);
			}
			else
			{
				//Rotate Right Flipper CCW until static position
				rightFlipper->rotateFlipper(false);
			}

			if (Keyboard::isKeyPressed(Keyboard::Space))
				ballLauncher->pullBack();
			else
				ballLauncher->release();

			ballLauncher->update();
			window.clear();
			window.draw(mouse_check);
			window.draw(pinball->getShape());
			window.draw(leftFlipper->getShape());
			window.draw(rightFlipper->getShape());
			window.draw(ballLauncher->getShape());

			window.draw(rectangle);
			window.draw(left_rectangle);
			window.draw(corner);
			window.draw(left_corner);
			window.draw(left_bound);
			window.draw(right_bound);
			window.draw(titleshadow);
			window.draw(scoreshadow);
			window.draw(title);
			window.draw(score);
			window.draw(score_box2);
			window.draw(score_box1);
			window.display();
			//count = 1;
		}

		if (user_choice == 7) {
			window.close();
		}


	}

	return 0;
}
