#include <SFML/Graphics.hpp>
#include "Header.h"
#include <fstream>
#include<string>

int GetFile()
{
	std::ifstream fin;
	int res;
	fin.open("HighScore.bin", std::ios::binary);
	if (!fin.is_open()) return 0;
	else
	{
		fin.read((char*)&res, sizeof(int));
	}
	fin.close();
	return res;
}
void SetFile(int HighScore)
{
	std::ofstream fout;
	fout.open("HighScore.bin", std::ios::binary);
	if (!fout.is_open()) return;
	else fout.write((char*)&HighScore, sizeof(int));
	fout.close();
}

int main()
{
	sf::Font* font = new sf::Font;
	if (!font->loadFromFile("arial.ttf")) exit(0);
	sf::Text text_score, text_high_score;
	short Score = 0;
	text_score.setFont(*font);
	text_score.setCharacterSize(30);
	text_score.setFillColor(sf::Color::Black);
	text_score.setPosition(660, 265);

	text_high_score.setFont(*font);
	text_high_score.setCharacterSize(30);
	text_high_score.setFillColor(sf::Color::Black);
	text_high_score.setPosition(695, 136);

	char strScore[8], strHighScore[8];
	int HighScore = GetFile();
	_itoa_s(HighScore, strHighScore, 10);
	text_high_score.setString(strHighScore);

	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(750, 550), "Snake!");
	window.setFramerateLimit(60);
	sf::Event event;
	sf::Clock clock;
	double timer = 0.2;
	Direction DIR = RIGHT;
	snake Snake, temp;
	apple Apple;
	Apple.set(Snake);

	sf::Texture startScreen;
	sf::Texture endScreen;
	sf::Texture Tiles;
	sf::Texture Background;
	startScreen.loadFromFile("startScreen.png");
	endScreen.loadFromFile("endScreen.png");
	Tiles.loadFromFile("TilesFinal.png");//вручную нарисовання картинка, с 7 разноцветными квадратиками
	Background.loadFromFile("BackgroundFinal.png");

	sf::Sprite SprBackground(Background);
	sf::Sprite SprTiles(Tiles);
	sf::Sprite StrScreen(startScreen);
	sf::Sprite EndScreen(endScreen);

	while (window.isOpen())
	{
		bool startGame = true;

		window.draw(StrScreen);
		window.display();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}

			if (event.type == sf::Event::KeyPressed) startGame = false;
		}
		if (!startGame) break;
	}

	while (window.isOpen())
	{
		timer = 0.2;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) 
					&& DIR != LEFT 
					&& (Snake.X[0] + 1 != Snake.X[1])) DIR = RIGHT;
				if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) 
					&& DIR != RIGHT
					&& (Snake.X[0] - 1 != Snake.X[1])) DIR = LEFT;
				if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) 
					&& DIR != DOWN
					&& (Snake.Y[0] - 1 != Snake.Y[1])) DIR = UP;
				if ((event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) && 
					DIR != UP
					&& (Snake.Y[0] + 1 != Snake.Y[1])) DIR = DOWN;
				else if (event.key.code == sf::Keyboard::LAlt || event.key.code == sf::Keyboard::RAlt)
				{
					bool pause = true;
					while (pause)
					{
						while (window.pollEvent(event))
						{
							if (event.type == sf::Event::Closed)
							{
								window.close();
								return 0;
							}
							if (event.type == sf::Event::KeyPressed) pause = false;
						}
					}
				}
				if (event.key.code == sf::Keyboard::Space) timer = 0.01;
				clock.restart();
				temp = Snake;
				temp.move(DIR);
				if (temp.X[0] == Apple.X && temp.Y[0] == Apple.Y)
				{
					Score++;
					Snake.X.push_back(0);
					Snake.Y.push_back(0);
					Snake.move(DIR);
					Apple.set(Snake);
				}
				else
				{
					Snake.move(DIR);
				}
				if (Snake.check())
				{
					if (Score > HighScore)
					{
						SetFile(Score);
					}
					window.clear();
					window.draw(EndScreen);
					window.display();
					clock.restart();
					sf::Event e;
					while (clock.getElapsedTime().asSeconds() < 0.5);
					while (window.isOpen())
					while (window.pollEvent(e))
					{
						if (e.type == sf::Event::Closed) {
							window.close();
							return 0;
						}

						if (e.type == sf::Event::KeyPressed) {
							window.close();
							return 0;
						}
					}
				}
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) timer = 0.01;
		}

		if (timer < clock.getElapsedTime().asSeconds())
		{
			clock.restart();
			temp = Snake;
			temp.move(DIR);
			if (temp.X[0] == Apple.X && temp.Y[0] == Apple.Y)
			{
				Score++;
				Snake.X.push_back(0);
				Snake.Y.push_back(0);
				Snake.move(DIR);
				Apple.set(Snake);
			}
			else
			{
				Snake.move(DIR);
			}

			if (Snake.check())
			{
				if (Score > HighScore)
				{
					SetFile(Score);
				}
				window.clear();
				window.draw(EndScreen);
				window.display();
				clock.restart();
				sf::Event e;
				while (clock.getElapsedTime().asSeconds() < 0.5);
				while (window.isOpen())
				while (window.pollEvent(e))
				{
					if (e.type == sf::Event::Closed) {
						window.close();
						return 0;
					}

					if (e.type == sf::Event::KeyPressed) {
						window.close();
						return 0;
					}
				}
			}
		}
		//Отрисовка
		window.clear();
		window.draw(SprBackground);
		window.draw(text_score);
		window.draw(text_high_score);
		for (int i = 1; i < Snake.X.size(); i++)
		{
			SprTiles.setTextureRect(sf::IntRect(25, 0, 25, 25));
			SprTiles.setPosition((1+Snake.X[i]) * 25 + 1, (1+Snake.Y[i]) * 25 + 1);
			window.draw(SprTiles);
		}

		SprTiles.setTextureRect(sf::IntRect(0, 0, 25, 25));
		SprTiles.setPosition((1+Snake.X[0]) * 25 + 1, (1+Snake.Y[0]) * 25 + 1);
		window.draw(SprTiles);
		
		SprTiles.setTextureRect(sf::IntRect(50, 0, 25, 25));
		SprTiles.setPosition((1+Apple.X) * 25 + 1, (1+Apple.Y) * 25 + 1);

		window.draw(SprTiles);


		_itoa_s(Score, strScore, 10);
		text_score.setString(strScore);

		if (Score > HighScore)
		{
			//SetFile(game.GetScore());
			text_high_score.setString(strScore);
		}
		window.draw(text_high_score);

		window.display();
	}
}