#include "Game.h"
using namespace std;

//private functions
void Game::initVar()
{
	this->window = nullptr;

	//Game Logic
	this->endGame = false;
	this->points = 0;
	this->health = 35;
	this->enemySpawnTimerMax = 4.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 26;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 768;
	this->videoMode.width = 1366;

	this->window = new sf::RenderWindow(this->videoMode, "My First Game", sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(60);
	

}

void Game::initFonts()
{
	if (this->font.loadFromFile("fonts/Squids.ttf"))
	{
		std::cout << "\nINFO::GAME::INITFONTS::Loading Fonts " << endl;
	}
	else
		std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts" << endl;
}


void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setPosition(20, 20);
	this->uiText.setCharacterSize(20);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}



void Game::initEnemies()
{
	this->enemy.setPosition(683.f, 384.f);
	this->enemy.setSize(sf::Vector2f(50.f, 50.f));
	this->enemy.setScale(sf::Vector2f(1.f, 1.f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(6.f);

}

//Constructors & Destructors
Game::Game()
{
	this->initVar();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;  //destructor
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Accessors



//functions
void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and set their type, color and positions randomly 
		-Sets a random position
		-Adds enemy to the vector

	*/



	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//randomize enemy type
	int type = rand() % 4;

	switch (type)
	{
	case 0:
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setOutlineColor(sf::Color::Red);
		this->enemy.setOutlineThickness(2.f);
		break;
	case 1:
		this->enemy.setSize(sf::Vector2f(40.f, 40.f));
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setOutlineColor(sf::Color::Magenta);
		this->enemy.setOutlineThickness(2.f);
		break;
	case 2:
		this->enemy.setSize(sf::Vector2f(15.f, 15.f));
		this->enemy.setFillColor(sf::Color::Black);
		this->enemy.setOutlineColor(sf::Color::Cyan);
		this->enemy.setOutlineThickness(2.f);
		break;
	default:
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		this->enemy.setFillColor(sf::Color::White);
		this->enemy.setOutlineColor(sf::Color::Green);
		this->enemy.setOutlineThickness(6.f);
		break;
	}


		//Spawn the enemy
		this->enemies.push_back(this->enemy);

		//Remove the enemies at the edge of screen

}

void Game::updateEnemies()
{
	/*
		@return void

		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max
		Moves enemies downwards
		Removes the the enemies at the endge of the screen
	*/

	//updating the Timer for enemy spawns
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
	else
		this->enemySpawnTimer += 1.f;
	}

	//Move and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 6.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << "\n";
		}
	}
	
	//Check if clicked upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{

					//Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Black)
						this->points += 10.f;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7.f;
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 5.f;
					else if (this->enemies[i].getFillColor() == sf::Color::White)
						this->points += 2.f;
					std::cout << "Points: " << this->points << "\n";

					//Delete the Enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}

			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//Rendering all the Enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
	target.draw(this->hhText);
}



void Game::updateEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		}
	}
}

void Game::updateMousePos()
{
	/*
	@ return void

	update mouse positions:
		- Mouse position relative to window (Vector2i)
		
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << endl;
	ss << "Health: " << this->health << endl;
	this->uiText.setString(ss.str());

}


void Game::update()
{
	//Event polling
	this->updateEvents();

	if (!this->endGame)
	{

		this->updateMousePos();

		this->updateText();

		this->updateEnemies();
	}

	//End Game condition
	if (this->health <= 0)
		this->endGame = true;
}	

void Game::render()
{
	/*
		Retrun void
		- clear old frame
		- render all objects
		- display frame in window
		
		Renders the game objects
	*/

	sf::Texture t;
	t.loadFromFile("fonts/bg2.png");
	sf::Sprite s(t);
	window->clear(sf::Color::White);
	window->draw(s);
	//Draw game objects here
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}


