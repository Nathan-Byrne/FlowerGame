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

	// Title Screen (Non-Graphic + Graphic)
	bool m_titleScreen{ true };

	sf::RectangleShape m_title;
	sf::Vector2f m_titleL;
	sf::Text m_titleText;
	
	// Background (Graphic)
	sf::Texture m_backgroundT;
	sf::Sprite m_backgroundS;

	// Flower (Non-Graphic)
	sf::RectangleShape m_flowerHitbox;
	sf::Vector2f m_flowerHitboxL;

};

#endif // !GAME_HPP

