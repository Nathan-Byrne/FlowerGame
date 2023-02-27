/// <summary>
/// author Nathan Byrne Feb 2023
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	// Setup Fonts + Sprites
	void setupSprite();
	void setupFlowerHitbox();
	void setupTitle();
	void setupBallEnemy();

	void setupFontAndText();
	void setupTitleText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	// Others
	bool m_graphicMode{ false };

	// Title Screen
	bool m_titleScreen{ true };

	sf::RectangleShape m_title;
	sf::Text m_titleText;

	sf::RectangleShape m_displayBox1;
	sf::Text m_displayText1;
	sf::Text m_graphicText;

	sf::RectangleShape m_displayBox2;
	sf::Text m_displayText2;

	std::string m_difficulty{ "Easy" }; // cover screen for hard
	sf::RectangleShape m_displayBox3;
	sf::Text m_displayText3;
	sf::Text m_difficultyText;
	
	// Background (Graphic)
	sf::Texture m_backgroundT;
	sf::Sprite m_backgroundS;

	// Flower (Non-Graphic)
	sf::RectangleShape m_flowerHitbox1;
	sf::Vector2f m_flowerHitbox1L;
	sf::RectangleShape m_flowerHitbox2;
	sf::Vector2f m_flowerHitbox2L; 
	sf::RectangleShape m_flowerHitbox3;
	sf::Vector2f m_flowerHitbox3L; 
	sf::RectangleShape m_flowerHitbox4;
	sf::Vector2f m_flowerHitbox4L;
	// Cannonball Enemy (Non-Graphic)
	sf::CircleShape m_ball;

};

#endif // !GAME_HPP

