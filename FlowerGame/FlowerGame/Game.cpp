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
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "Flower Game by Nathan Byrne" },
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
		if (sf::Keyboard::F1 == t_event.key.code) // Enable/ disable graphic mode (via F1)
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
	if (m_titleScreen) // Constantly check for graphic toggle
	{
		setupTitleText();
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
		// Display Display Boxes
		m_window.draw(m_displayBox1);
		m_window.draw(m_displayText1);
		m_window.draw(m_graphicText);

		m_window.draw(m_displayBox2);
		m_window.draw(m_displayText2);

		m_window.draw(m_displayBox3);
		m_window.draw(m_displayText3);
		// m_window.draw(m_difficulty);
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
			// Render Flower Hitboxs
			m_window.draw(m_flowerHitbox1); 
			m_window.draw(m_flowerHitbox2);
			m_window.draw(m_flowerHitbox3);
			m_window.draw(m_flowerHitbox4);
			m_window.draw(m_ball); // Render Ball/ Projectile
		}
	}

	// REMOVE BELOW
	// m_window.draw(m_logoSprite);


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
	setupBallEnemy();

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
	// Hitbox 1
	m_flowerHitbox1.setFillColor(sf::Color::Green); // Colour of hitbox (Non-graphic only)
	m_flowerHitbox1.setSize(sf::Vector2f{ 32.0f,100.0f }); // Size of flower hitbox 
	m_flowerHitbox1L = sf::Vector2f{ (SCREEN_WIDTH / 5) - 16.0f,545.0f }; // Location of flower
	m_flowerHitbox1.setPosition(m_flowerHitbox1L);

	// Hitbox 2
	m_flowerHitbox2.setFillColor(sf::Color::Yellow); 
	m_flowerHitbox2.setSize(sf::Vector2f{ 32.0f,100.0f });  
	m_flowerHitbox2L = sf::Vector2f{ ((SCREEN_WIDTH / 5) * 2) - 16.0f,545.0f };
	m_flowerHitbox2.setPosition(m_flowerHitbox2L);

	// Hitbox 3
	m_flowerHitbox3.setFillColor(sf::Color::Blue); 
	m_flowerHitbox3.setSize(sf::Vector2f{ 32.0f,100.0f });  
	m_flowerHitbox3L = sf::Vector2f{ ((SCREEN_WIDTH / 5) * 3) - 16.0f,545.0f };
	m_flowerHitbox3.setPosition(m_flowerHitbox3L);

	// Hitbox 4
	m_flowerHitbox4.setFillColor(sf::Color::Magenta); 
	m_flowerHitbox4.setSize(sf::Vector2f{ 32.0f,100.0f }); 
	m_flowerHitbox4L = sf::Vector2f{ ((SCREEN_WIDTH / 5) * 4) - 16.0f,545.0f };
	m_flowerHitbox4.setPosition(m_flowerHitbox4L);

	// SCREEN_WIDTH/5
}

void Game::setupBallEnemy()
{
	m_ball.setFillColor(sf::Color::Black); // Colour
	m_ball.setRadius(10.0f); // Radius
	m_ball.setOrigin(10.0f, 10.0f); // Origin
	m_ball.setPosition(100.0f, 100.0f); // Temp
}

void Game::setupTitle()
{
	// Temp Background
	m_title.setFillColor(sf::Color::Black);
	m_title.setSize(sf::Vector2f{ 800.0f,600.0f });

	// Display Boxes
	m_displayBox1.setFillColor(sf::Color::Red);
	m_displayBox1.setSize(sf::Vector2f{600.0f,100.0f});
	m_displayBox1.setPosition(100.0f, 175.0f);

	m_displayBox2.setFillColor(sf::Color::Red);
	m_displayBox2.setSize(sf::Vector2f{ 600.0f,100.0f });
	m_displayBox2.setPosition(100.0f, 425.0f);

	m_displayBox3.setFillColor(sf::Color::Red);
	m_displayBox3.setSize(sf::Vector2f{ 600.0f,100.0f });
	m_displayBox3.setPosition(100.0f, 300.0f);
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
	m_titleText.setPosition(100.0f, 20.0f);
	m_titleText.setCharacterSize(80U);
	m_titleText.setOutlineColor(sf::Color::Red);
	m_titleText.setFillColor(sf::Color::Black);
	m_titleText.setOutlineThickness(3.0f);

	// Display Box 1
	m_displayText1.setFont(m_ArialBlackfont);
	m_displayText1.setString("Graphic Mode: ");
	m_displayText1.setPosition(110.0f, 195.0f);
	m_displayText1.setCharacterSize(40U);
	m_displayText1.setOutlineColor(sf::Color::Black);
	m_displayText1.setFillColor(sf::Color::Yellow);
	m_displayText1.setOutlineThickness(3.0f);

	// Graphic Mode Toggle
	if (m_graphicMode == true) // Graphic Mode Enabled
	{
		m_graphicText.setFont(m_ArialBlackfont);
		m_graphicText.setString("On");
		m_graphicText.setPosition(440.0f, 195.0f);
		m_graphicText.setCharacterSize(40U);
		m_graphicText.setOutlineColor(sf::Color::Black);
		m_graphicText.setFillColor(sf::Color::Yellow);
		m_graphicText.setOutlineThickness(3.0f);
	}
	else // Graphic Mode Disabled
	{
		m_graphicText.setFont(m_ArialBlackfont);
		m_graphicText.setString("Off");
		m_graphicText.setPosition(440.0f, 195.0f);
		m_graphicText.setCharacterSize(40U);
		m_graphicText.setOutlineColor(sf::Color::Black);
		m_graphicText.setFillColor(sf::Color::Yellow);
		m_graphicText.setOutlineThickness(3.0f); 
	}

	// Start Game
	m_displayText2.setFont(m_ArialBlackfont);
	m_displayText2.setString("Press Space to Start Game ");
	m_displayText2.setPosition(110.0f, 450.0f);
	m_displayText2.setCharacterSize(40U);
	m_displayText2.setOutlineColor(sf::Color::Black);
	m_displayText2.setFillColor(sf::Color::Yellow);
	m_displayText2.setOutlineThickness(3.0f);

	// Difficulty Change
	m_displayText3.setFont(m_ArialBlackfont);
	m_displayText3.setString("Difficulty: ");
	m_displayText3.setPosition(110.0f, 325.0f);
	m_displayText3.setCharacterSize(40U);
	m_displayText3.setOutlineColor(sf::Color::Black);
	m_displayText3.setFillColor(sf::Color::Yellow);
	m_displayText3.setOutlineThickness(3.0f);

	// Do later
	if (m_difficulty == "Easy")
	{

	}
	else if (m_difficulty == "Medium")
	{

	}
	else // Hard
	{

	}
}