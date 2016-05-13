#define SFML STATIC
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <stdlib.h>
#include <iostream>

using namespace std;

class GHAnimatedSprite
{
public:
	//Things we need to store
	sf::Sprite sprite;
	int currentFrame;
	float timeSinceLastChange;


	//constructor
	GHAnimatedSprite(sf::Texture & myTexture);
	void Update(float timeSinceLastFrame);

	// default constructor
	GHAnimatedSprite();
};

// enum to contain all the gamestates for switch
enum Gamestate {Welcome, Game, End, Win};

// function to convert into to string for UI
string toString(int myInt)
{
	ostringstream os;
	os << myInt;
	return os.str();
}

int main(int, char const**)
{
	// initialise gamestate
	Gamestate newGame = Welcome;

	// view stuff
	sf::View view;
	int myX = 0;

	// declare functions
	void Inputer(sf::Sprite &playerSprite, float deltaTime);
	void Reset(sf::Sprite &playerSprite);
	void Patrol(GHAnimatedSprite &ghSpriteGhost);
	void KeyCaught(GHAnimatedSprite &ghSpriteKey);

	// bool to store information about direction movement of ghost enemy
	bool moveRight = false;

	// vector to store the most recent position of the player
	sf::Vector2f playerWasAt;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Set the Icon
	sf::Image icon;
	if (!icon.loadFromFile("icon.png")) 
	{
		//return EXIT_FAILURE;
		//error
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	// create fire sprite
	sf::Texture fire1Texture;
	if (!fire1Texture.loadFromFile("FireSprite.png")) 
	{
		//return EXIT_FAILURE;
	}
	//reference pointer to the texture
	sf::Texture &ref_fire1Texture = fire1Texture;

	// array for animated fire sprite
	// set texture,texture rect, and position for sprites
	GHAnimatedSprite ghSpriteFire[8];
	for (int i = 0; i < 8; i++)
	{
		ghSpriteFire[i].sprite.setTexture(ref_fire1Texture);
		ghSpriteFire[i].sprite.setTextureRect(sf::IntRect(64 * ghSpriteFire[i].currentFrame, 0, 64, 64));
		ghSpriteFire[0].sprite.setPosition(64, 256);
		ghSpriteFire[1].sprite.setPosition(224, 256);
		ghSpriteFire[2].sprite.setPosition(384, 256);
		ghSpriteFire[3].sprite.setPosition(544, 256);
		ghSpriteFire[4].sprite.setPosition(1152, 900);
		ghSpriteFire[5].sprite.setPosition(1400, 800);
		ghSpriteFire[6].sprite.setPosition(1580, 800);
		ghSpriteFire[7].sprite.setPosition(1400, 1000);
	}

	// create and load texture for spike sprite
	sf::Texture spike1Texture;
	if (!spike1Texture.loadFromFile("SpikeSprite.png"));
	{
		// return EXIT_FAILURE;
	}
	// reference pointer to texture
	sf::Texture &ref_spike1Texture = spike1Texture;

	// array for animated spike sprite
	// set texture,texture rect, and position for sprites
	GHAnimatedSprite ghSpriteSpike[8];
	for (int i = 0; i < 8; i++)
	{
		ghSpriteSpike[i].sprite.setTexture(ref_spike1Texture);
		ghSpriteSpike[i].sprite.setPosition(1654, 512 + (i * 64));
		ghSpriteSpike[i].sprite.setTextureRect(sf::IntRect(64 * ghSpriteFire[i].currentFrame, 0, 64, 64));
	}

	// create and load texture for ghost sprite
	sf::Texture ghost1Texture;
	if (!ghost1Texture.loadFromFile("GhostSprite.png"));
	{
		// return EXIT_FAILURE;
	}
	// reference pointer to texture
	sf::Texture &ref_ghost1Texture = ghost1Texture;

	// set texture and position for animated ghost sprite
	GHAnimatedSprite ghSpriteGhost(ref_ghost1Texture);
	ghSpriteGhost.sprite.setPosition(64, 400);

	// create and load texture for key sprite
	sf::Texture key1Texture;
	if (!key1Texture.loadFromFile("KeySprite.png"));
	{
		// return EXIT_FAILURE;
	}
	// reference pointer to texture
	sf::Texture &ref_key1Texture = key1Texture;

	// set texture and position for animated key sprite
	GHAnimatedSprite ghSpriteKey(ref_key1Texture);
	ghSpriteKey.sprite.setPosition(1780.0f, 512.0f);

	// declare and initialise bool to store whether player has key
	bool haveKey = false;

	// array for brick sprite
	// set texture,texture rect, and position for sprites
	sf::Texture wallBrickT;
	wallBrickT.loadFromFile("WallBrick.png");
	sf::Sprite wallBrick[130];

	for (int i = 0; i < 12; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(i * 64, 0);
	}
	for (int i = 13; i < 23; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(0, (i - 12) * 64);
	}
	for (int i = 24; i < 31; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(704, (i - 23) * 64);
	}
	for (int i = 32; i < 48; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition((i - 31) * 64, 640);
	}
	for (int i = 49; i < 55; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(704 + (i - 48) * 64, 448);
	}
	for (int i = 56; i < 64; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1088, 576 + (i - 55) * 64);
	}
	for (int i = 65; i < 77; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1024 + (i - 64) * 64, 1152);
	}
	for (int i = 78; i < 90; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1856, 384 + (i - 77) * 64);
	}
	for (int i = 91; i < 100; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1216 + (i - 90) * 64, 448);
	}
	for (int i = 101; i < 108; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1088, (i - 101) * 64);
	}
	for (int i = 109; i < 112; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1280, 320 + (i - 109) * 64);
	}
	for (int i = 113; i < 117; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1344 + (i - 113) * 64, 320);
	}
	for (int i = 118; i < 125; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1152 + (i - 118) * 64, 0);
	}
	for (int i = 126; i < 130; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1536, 64 + (i - 126) * 64);
	}


	// declare and initialise texture and texture rect for start page
	sf::Texture welcomeScreen;
	if (welcomeScreen.loadFromFile("TitlePage.png"))
	{
		// return EXIT_FAILURE;
	}
	sf::Sprite welcomePage;
	welcomePage.setTexture(welcomeScreen);
	welcomePage.setTextureRect(sf::IntRect(0, 0, 800, 600));

	// declare and initialise texture and texture rect for win game page
	sf::Texture winPageT;
	if (winPageT.loadFromFile("WinPage.png"))
	{
		//return EXIT_FAILURE;
	}
	sf::Sprite winPage;
	winPage.setTexture(winPageT);
	winPage.setTextureRect(sf::IntRect(0, 0, 800, 600));
	winPage.setPosition(sf::Vector2f(0, 0));

	// declare and initialise texture and texture rect for game over page
	sf::Texture lostGameT;
	if (lostGameT.loadFromFile("GameOverPage.png"))
	{
		//return EXIT_FAILURE;
	}
	sf::Sprite lostGame;
	lostGame.setTexture(lostGameT);
	lostGame.setTextureRect(sf::IntRect(0, 0, 800, 600));

	// declare and initialise texture, texture rect, and position for player sprite
	sf::Texture playerSpriteT;
	playerSpriteT.loadFromFile("PlayerSprite.png");
	{
		// return EXIT_FAILURE;
	}
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerSpriteT);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	playerSprite.setPosition(64, 64);

	// declare and initialise colour, vector and position of rectangle for door
	sf::RectangleShape door(sf::Vector2f(128, 64));
	door.setFillColor(sf::Color::Magenta);
	door.setPosition(1152, 320);
	// declare and initialise bool to store whether the door is active
	bool doorOpen = false;

	// declare and initialise colour, vector and position of rectangle for trap
	sf::RectangleShape trap(sf::Vector2f(64, 512));
	trap.setFillColor(sf::Color::Transparent);
	trap.setPosition(1588, 512);

	// declare and initialise bool to store whether the trap is active
	bool spikesOn = false;

	// create and load texture for treasure sprite
	sf::Texture treasureSpriteT;
	treasureSpriteT.loadFromFile("TreasureSprite.png");
	{
		// return EXIT_FAILURE;
	}
	
	// array for treasure sprite
	// set texture,texture rect, and position for sprites
	sf::Sprite treasureSprite[3];
	for (int i = 0; i < 3; i++)
	{
		treasureSprite[i].setTexture(treasureSpriteT);
		treasureSprite[i].setTextureRect(sf::IntRect(0, 0, 64, 64));
		treasureSprite[0].setPosition(1408, 128);
		treasureSprite[1].setPosition(1408, 256);
		treasureSprite[2].setPosition(1152, 128);
	}
	
	// array and loop for boolean value to store which treasure sprites are active
	bool haveTreasure[3];
	for (int i = 0; i < 3; i++)
	{
		haveTreasure[i] = false;
	}

	// int to count picked up treasure
	int treasureCount = 0;

	// declare and load font from file
	sf::Font font;
	if (!font.loadFromFile("pixel.ttf"))
	{
		return EXIT_FAILURE;
	}

	// declare text for UI output
	sf::Text treasureText;

	// set int element of text to string
	treasureText.setString("TREASURE:  " + toString(treasureCount));

	// set font, size, and colour of font
	treasureText.setFont(font);
	treasureText.setCharacterSize(45);
	treasureText.setColor(sf::Color::Yellow);

	// int to count player's current number of collected keys this round
	int keyCount = 0;

	// declare text for UI output
	sf::Text keyText;

	// set int element of text to string
	keyText.setString("KEYS:  " + toString(keyCount));

	// set font, size, and colour of font
	keyText.setFont(font);
	keyText.setCharacterSize(45);
	keyText.setColor(sf::Color::Yellow);



	// clock variables for animated sprite frame rate
	sf::Clock clock1;
	sf::Time elapsed1;
	float timeSinceLastFrameAsFloat = 0.0f;
	float lastTimeAsFloat = 0.0f;

	// load a music to play from file
	sf::Music music;
	if (!music.openFromFile("Smb_under.ogg"))
	{
		return EXIT_FAILURE;
	}
	
	// play the music
	music.play();



	// Start the game loop
	while (window.isOpen())
	{

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) 
			{
				window.close();
			}
			
			// store the player's current position for collision check
			playerWasAt.x = playerSprite.getPosition().x;
			playerWasAt.y = playerSprite.getPosition().y;
		}

		// game switch to control flow
		switch(newGame)
		{

		// case for starting screen
		case Welcome:
			
			// start game on return
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				newGame = Game;
			}

			// clear window
			window.clear();

			// draw to window
			window.draw(welcomePage);

			// display to window
			window.display();

			// break case
			break;

		// case for game
		case Game:

			// declare inputer function within scope
			Inputer(playerSprite, timeSinceLastFrameAsFloat);

			// UI output to player
			keyText.setString("KEYS:  " + toString(keyCount));
			treasureText.setString("TREASURE:  " + toString(treasureCount));

			// set position of UI text
			keyText.setPosition(playerSprite.getPosition().x - 500, playerSprite.getPosition().y - 520);
			treasureText.setPosition(playerSprite.getPosition().x - 500, playerSprite.getPosition().y - 480);

			// collision check between player and walls
			// using for loop to iterate through array of sprites
			for (int i = 0; i < 130; i++) 
			{
				// positional comparision between player and wall to check for collision
				if ((abs((int)playerSprite.getPosition().x - (int)wallBrick[i].getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)wallBrick[i].getGlobalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)wallBrick[i].getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)wallBrick[i].getGlobalBounds().height)))) {

					// if there was a collision, undo player movement
					playerSprite.setPosition(playerWasAt.x, playerWasAt.y);
				}
			}

			// positional comparision between player and door to check for collision
			if ((abs((int)playerSprite.getPosition().x - (int)door.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)door.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)door.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)door.getLocalBounds().height))))
			{
				// if player has key, allow player to open door
				if (haveKey == true)
				{
					doorOpen = true;
				}

				// when door is not open
				if (doorOpen == false)
				{
					// if there was a collision, undo player movement;
					playerSprite.setPosition(playerWasAt.x, playerWasAt.y);
				}
			}

			// positional comparision between player and trap to check for collision
			if ((abs((int)playerSprite.getPosition().x - (int)trap.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)trap.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)trap.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)trap.getLocalBounds().height))))
			{
				// if player collides with trap, turn on the spikes
				spikesOn = true;
			}

			// collision check between player and fire
			// using for loop to iterate through array of sprites
			for (int i = 0; i < 8; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteFire[i].sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteFire[i].sprite.getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)ghSpriteFire[i].sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteFire[i].sprite.getLocalBounds().height))))
				{
					// if there was a collision, kill player; move gamestate to end
					newGame = End;

				}
			}

			// collision check between player and spikes
			// using for loop to iterate through array of sprites
			for (int i = 0; i < 8; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteSpike[i].sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteSpike[i].sprite.getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)ghSpriteSpike[i].sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteSpike[i].sprite.getLocalBounds().height))))
				{
					// if there was a collision, kill player; move gamestate to end
					newGame = End;
				}
			}

			// positional comparision between player and ghost to check for collision
			if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteGhost.sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteGhost.sprite.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)ghSpriteGhost.sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteGhost.sprite.getLocalBounds().height))))
			{
				// if there was a collision, kill player; move gamestate to end
				newGame = End;
			}

			// positional comparision between player and key to check for collision
			if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteKey.sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteKey.sprite.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)ghSpriteKey.sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteKey.sprite.getLocalBounds().height))))
			{
				// on collision change key bool to true and output key collection to UI
				haveKey = true;
				keyCount = 1;
			}

			// collision check between player and treasure
			// using for loop to iterate through array of sprites
			for (int i = 0; i < 3; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)treasureSprite[i].getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)treasureSprite[i].getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)treasureSprite[i].getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)treasureSprite[i].getLocalBounds().height))))
				{
					// when player collides with treasure, if that treasure bool in the array was false, turn to true, and add to treasure count in UI
					if (haveTreasure[i] == false)
					{
						treasureCount ++;
						haveTreasure[i] = true;
					}
				}
			}

			// if all treasure has been collected, move gamestate to win case
			if (treasureCount == 3)
			{
				newGame = Win;
			}

			// control for animated ghost sprite movement
			// if ghost moving right, move at 64 pixels multiplied by time float variable
			if(moveRight) 
			{
				ghSpriteGhost.sprite.move(64 * timeSinceLastFrameAsFloat, 0);

				// when ghost reaches x = 607, set move right bool to false
				if (ghSpriteGhost.sprite.getPosition().x > 608)
				{
					moveRight = false;
				}
			}
			
			// if ghost moving left, move at 64 pixels left (or negative 64 right) multiplied by time float variable
			if (!moveRight) {
				ghSpriteGhost.sprite.move(-64 * timeSinceLastFrameAsFloat, 0);

				// when ghost reaches x = 64, set move right bool to true
				if (ghSpriteGhost.sprite.getPosition().x < 64)
				{
					moveRight = true;
				}
			}


			// change the camera according to the player position
			view.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
			window.setView(view);

			// game timer
			elapsed1 = clock1.getElapsedTime();
			timeSinceLastFrameAsFloat = elapsed1.asSeconds() - lastTimeAsFloat;
			lastTimeAsFloat = elapsed1.asSeconds();


			// for loop for the array of animated fire sprite to iterate through frames
			for (int i = 0; i < 8; i++)
			{
				ghSpriteFire[i].Update(timeSinceLastFrameAsFloat);
			}

			// for loop for the array of animated spike sprite to iterate through frames
			for (int i = 0; i < 8; i++)
			{
				ghSpriteSpike[i].Update(timeSinceLastFrameAsFloat);
			}

			// for loop for animated ghost sprite to iterate through frames
			ghSpriteGhost.Update(timeSinceLastFrameAsFloat);

			// for loop for animated key sprite to iterate through frames
			ghSpriteKey.Update(timeSinceLastFrameAsFloat);

			// Clear screen
			window.clear();

			// draw ghost sprite
			window.draw(ghSpriteGhost.sprite);

			// draw door when the bool is set to not open
			if (doorOpen == false)
			{
				window.draw(door);
			}

			// draw key if player has not yet picked it up
			if (haveKey == false)
			{
				window.draw(ghSpriteKey.sprite);
			}

			// for loop to draw array of treasure who's boolean value hasn't yet been changed by player collision
			for (int i = 0; i < 3; i++)
			{
				if (haveTreasure[i] == false)
				{
					window.draw(treasureSprite[i]);
				}
			}

			// for loop to draw array of wall bricks
			for (int i = 0; i < 130; i++)
			{
				window.draw(wallBrick[i]);
			}

			// for loop to draw array of fire sprites
			for (int i = 0; i < 8; i++)
			{
				window.draw(ghSpriteFire[i].sprite);
			}

			// draw trap
			window.draw(trap);

			// draw spikes if bool for spikes is true
			if (spikesOn == true)
			{
				for (int i = 0; i < 8; i++)
				{
					window.draw(ghSpriteSpike[i].sprite);
				}
			}

			// draw the player (last so it's on top)
			window.draw(playerSprite);
			
			// draw UI text
			window.draw(keyText);
			window.draw(treasureText);

			// Update the window
			window.display();
			
			//End of the Game State
			myX++;
			break;

		// case for game over
		case End:
			
			// reset player position, all boolean fields, and UI counters
			playerSprite.setPosition(64, 64);
			haveKey = false;
			doorOpen = false;
			spikesOn = false;
			for (int i = 0; i < 3; i++)
			{
				haveTreasure[i] = false;
			}
			treasureCount = 0;
			keyCount = 0;

			// start new game on return
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				newGame = Game;
			}

			// clear screen
			window.clear();

			// draw game over screen
			window.draw(lostGame);

			// update display
			window.display();
			break;

		// case for player winning game
		case Win:

			// reset player position, all boolean fields, and UI counters
			playerSprite.setPosition(64, 64);
			haveKey = false;
			doorOpen = false;
			spikesOn = false;
			for (int i = 0; i < 3; i++)
			{
				haveTreasure[i] = false;
			}
			treasureCount = 0;
			keyCount = 0;

			// start new game on return
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				newGame = Game;
			}

			// clear screen
			window.clear();

			// draw winning page sprite
			window.draw(winPage);

			// update display
			window.display();
		}
	}
	return 0;
}


// fucntion to handle player input during the game
void Inputer(sf::Sprite &playerSprite, float deltaTime) 
{
	// Check the boundry
	int boundry[4] = 
	{ 
		0,
		0,
		4000,
		4000 
	};
	
	// declare vector2f variable to store player position
	sf::Vector2f pos = playerSprite.getPosition();

	// move player at a velocity of 300 * variable deltaTime
	float velocity = 300.0f * deltaTime;

	// take key input from player, check boundary, and move accordingly at stored velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		if (pos.x > boundry[0]) playerSprite.move(-velocity, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (pos.x < boundry[2]) playerSprite.move(velocity, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		if (pos.y > boundry[1]) playerSprite.move(0, -velocity);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		if (pos.y < boundry[3]) playerSprite.move(0, velocity);
	}
}


// constructor for animated sprite class
// pass in texture
GHAnimatedSprite::GHAnimatedSprite(sf::Texture & myTexture) 
{
	// store information related to frame rate 
	currentFrame = 0;
	timeSinceLastChange = 0.0f;

	// set textures and texture rect for sprite
	sprite.setTexture(myTexture);
	sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));
}

// default constructor for animated sprite class
GHAnimatedSprite::GHAnimatedSprite()
{
	// store information related to frame rate 
	currentFrame = 0;
	timeSinceLastChange = 0.0f;
}

// update fucntion for animated sprite class
// pass in float that stores the time since last frame
void GHAnimatedSprite::Update(float timeSinceLastFrame) 
{
	// count the time change
	timeSinceLastChange += timeSinceLastFrame;
	if (timeSinceLastChange >= 0.25f) 
	{
		// reset the timer
		timeSinceLastChange = 0.0f;

		//increment the frame counter
		if (currentFrame >= 3) 
		{
			currentFrame = 0;
		}
		else 
		{
			currentFrame++;
		}

		//change the section of the texture
		sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));
	}
}