#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
/*
	Class that acts as the Game Engine / wrapper class


*/


class Game
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	sf::Event stuff;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;
	sf::Text hhText;

	//Game Logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//private functions
	void initVar();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemies();
public:
	//Constructor & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;


	//functions
	void menu();
	void spawnEnemy();
	void updateEnemies();
	void updateEvents();
	void updateMousePos();
	void updateText();
	void update();
	void render();
	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);



};