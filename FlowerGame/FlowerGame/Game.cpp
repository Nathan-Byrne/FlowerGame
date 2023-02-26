/// <summary>
/// @author Nathan Byrne
/// @date Feb 2023
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Flower Game by Nathan Byrne" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}

	// Only works on Title Screen
	if (m_titleScreen == true)
	{
		if (sf::Keyboard::Space == t_event.key.code) // Enter game, remove title screen
		{
			m_titleScreen = false;
		}
		if (sf::Keyboard::Num9 == t_event.key.code) // Enable/ disable graphic mode (via num 9)
		{
			m_graphicMode = !m_graphicMode;
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	if (m_titleScreen == true) // Title Screen 
	{
	    m_window.draw(m_title); // Render Title BG
	    m_window.draw(m_titleText); // Render Title Text
	}
	else // Game
	{
		if (m_graphicMode == true) // Graphic Mode On
		{

		}
		else // Graphic Mode Off
		{
			// Non-Graphic Renders
			m_window.draw(m_backgroundS); // Render Background
			m_window.draw(m_flowerHitbox); // Render Flower Hitbox
		}
	}

	// REMOVE BELOW
	m_window.draw(m_logoSprite);


	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	// Call Setup Functions
	setupTitleText();

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	// Call Setup Functions
	setupFlowerHitbox();
	setupTitle();


	// Possible Backgrounds:
	// purpleBG.jpg
	// grassSky.jpg (maybe)
	// stoneBG.jpg (best)

	// Load Background
	if (!m_backgroundT.loadFromFile("ASSETS\\IMAGES\\stoneBG.jpg"))
	{
		std::cout << "Problem loading background" << std::endl;
	}
	m_backgroundS.setTexture(m_backgroundT);
	

	// REMOVE STUFF BELOW
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}

void Game::setupFlowerHitbox()
{
	m_flowerHitbox.setFillColor(sf::Color::Green); // Colour of hitbox (Non-graphic only)
	m_flowerHitbox.setSize(sf::Vector2f{ 32.0f,100.0f }); // Size of flower hitbox 
	m_flowerHitboxL = sf::Vector2f{ 420.0f,545.0f }; // Location of flower
	m_flowerHitbox.setPosition(m_flowerHitboxL);
}

void Game::setupTitle()
{
	// Temp Background
	m_title.setFillColor(sf::Color::Black);
	m_title.setSize(sf::Vector2f{ 800.0f,600.0f });

}

void Game::setupTitleText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "Problem loading arial black font" << std::endl;
	}
	m_titleText.setFont(m_ArialBlackfont);
	m_titleText.setString("Flower Game");
	m_titleText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_titleText.setPosition(40.0f, 40.0f);
	m_titleText.setCharacterSize(80U);
	m_titleText.setOutlineColor(sf::Color::Red);
	m_titleText.setFillColor(sf::Color::Black);
	m_titleText.setOutlineThickness(3.0f);
}