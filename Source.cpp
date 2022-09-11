#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
using namespace std;
using namespace sf;


void menu()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "First window!");
	sf::Texture t;
	t.loadFromFile("fonts/bg1.png");
	sf::Sprite s(t);


	while (window.isOpen()) {
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
					break;
				}
			if (event.key.code == sf::Keyboard::Return)
			{
				//Init srand (seed)
				std::srand(static_cast<unsigned>(time(NULL)));

				//Initialize Game Engine
				Game game;


				//game loop
				while (game.running() && !game.getEndGame())
				{
					//Event polling


					//update game state
					game.update();

					//render
					game.render();

					//draw your game

				}
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

				}
				if (event.mouseButton.y > 550 && event.mouseButton.y < 618 && event.mouseButton.x > 500 && event.mouseButton.x < 867)
				{
				cout << "You are clicking Button 3\n";
					window.close();
				}
				if (event.mouseButton.y > 350 && event.mouseButton.y < 418 && event.mouseButton.x > 500 && event.mouseButton.x < 867)
				{
					//Init srand (seed)
					std::srand(static_cast<unsigned>(time(NULL)));
					//Initialize Game Engine
					Game game;


					//game loop
					while (game.running() && !game.getEndGame())
					{
						//Event polling


						//update game state
						game.update();

						//render
						game.render();

						//draw your game

					}
				}
				cout << "You are clicking Button 1\n";
				
			}

			window.clear(sf::Color::White);
				// Draw here.
			window.draw(s);
				sf::Font titlefont;
				sf::Font menuFont;

				titlefont.loadFromFile("fonts/wintersolstice.ttf");
				menuFont.loadFromFile("fonts/Squids.ttf");

				sf::Text title;
				title.setFont(titlefont);
				title.setString("Cascading Boxes!");
				title.setCharacterSize(88);
				title.setPosition(450, 180);
				title.setFillColor(sf::Color::Blue);
				title.setOutlineColor(sf::Color::Red);
				title.setOutlineThickness(2);

				window.draw(title);

				sf::Text menuText1;
				menuText1.setFont(titlefont);
				menuText1.setString("Play");
				menuText1.setCharacterSize(48);
				menuText1.setPosition(640, 350);
				menuText1.setFillColor(sf::Color::White);
				/*menuText1.setOutlineColor(sf::Color::Red);
				menuText1.setOutlineThickness(2);*/

				window.draw(menuText1);

				sf::RectangleShape menuButton1(sf::Vector2f(366.0f, 68.0f));
				menuButton1.setFillColor(sf::Color::Transparent);
				menuButton1.setPosition(500, 350);
				//menuButton1.setOrigin(menuButton1.getSize().x / 2, menuButton1.getSize().y / 2);
				menuButton1.setOutlineColor(sf::Color::Blue);
				menuButton1.setOutlineThickness(4.f);
				
				window.draw(menuButton1);

				sf::Text menuText2;
				menuText2.setFont(titlefont);
				menuText2.setString("Leaderboard");
				menuText2.setCharacterSize(48);
				menuText2.setPosition(590, 450);
				menuText2.setFillColor(sf::Color::White);
				/*menuText1.setOutlineColor(sf::Color::Red);
				menuText1.setOutlineThickness(2);*/

				window.draw(menuText2);

				sf::RectangleShape menuButton2(sf::Vector2f(366.0f, 68.0f));
				menuButton2.setFillColor(sf::Color::Transparent);
				menuButton2.setPosition(500, 450);
				//menuButton1.setOrigin(menuButton2.getSize().x / 2, menuButton1.getSize().y / 2);
				menuButton2.setOutlineColor(sf::Color::Blue);
				menuButton2.setOutlineThickness(4.f);

				window.draw(menuButton2);

				sf::RectangleShape menuButton3(sf::Vector2f(366.0f, 68.0f));
				menuButton3.setFillColor(sf::Color::Transparent);
				menuButton3.setPosition(500, 550);
				//menuButton1.setOrigin(menuButton3.getSize().x / 2, menuButton1.getSize().y / 2);
				menuButton3.setOutlineColor(sf::Color::Blue);
				menuButton3.setOutlineThickness(4.f);
				
				window.draw(menuButton3);

				sf::Text menuText3;
				menuText3.setFont(titlefont);
				menuText3.setString("Exit");
				menuText3.setCharacterSize(48);
				menuText3.setPosition(650, 550);
				menuText3.setFillColor(sf::Color::White);
				/*menuText1.setOutlineColor(sf::Color::Red);
				menuText1.setOutlineThickness(2);*/

				window.draw(menuText3);

				window.display();



			}
		}
	}

int main()
{
	//Init srand (seed)
	std::srand(static_cast<unsigned>(time(NULL)));

	menu();


	return 0;

}
	
