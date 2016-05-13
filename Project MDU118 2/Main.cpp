
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <sstream>

// Here is a small helper for you ! Have a look.

#include <stdlib.h>     /* abs */
#include <iostream>

using namespace std;

class GHAnimatedSprite// : public sf::Sprite
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

enum Gamestate {Welcome, Game, End};

string toString(int myInt)
{
	ostringstream os;
	os << myInt;
	return os.str();
}

int main(int, char const**)
{
	Gamestate newGame = Welcome;

	//VIEW STUFF
	sf::View view;
	int myX = 0;

	// declare functions
	void Inputer(sf::Sprite &playerSprite, float deltaTime);
	void Reset(sf::Sprite &playerSprite);
	void Patrol(GHAnimatedSprite &ghSpriteGhost);
	void KeyCaught(GHAnimatedSprite &ghSpriteKey);





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

	// FIRE SPRITE
	sf::Texture fire1Texture;
	if (!fire1Texture.loadFromFile("FireSprite.png")) 
	{
		//return EXIT_FAILURE;
		//error
	}
	//reference pointer to the texture
	sf::Texture &ref_fire1Texture = fire1Texture;


	// SPIKE SPRITE
	sf::Texture spike1Texture;
	if (!spike1Texture.loadFromFile("SpikeSprite.png"));
	{
		//error
	}
	// reference pointer to texture
	sf::Texture &ref_spike1Texture = spike1Texture;

	// GHOST SPRITE
	sf::Texture ghost1Texture;
	if (!ghost1Texture.loadFromFile("GhostSprite.png"));
	{
		//error
	}
	// reference pointer to texture
	sf::Texture &ref_ghost1Texture = ghost1Texture;

	// KEY SPRITE
	sf::Texture key1Texture;
	if (!key1Texture.loadFromFile("KeySprite.png"));
	{
		//error
	}
	// reference pointer to texture
	sf::Texture &ref_key1Texture = key1Texture;

	//
	//GH Animated Sprite
	GHAnimatedSprite ghSpriteFire[5];
	for (int i = 0; i < 5; i++)
	{
		ghSpriteFire[i].sprite.setTexture(ref_fire1Texture);
		ghSpriteFire[i].sprite.setPosition(64 + i * 64.0f, 256.0f);
		ghSpriteFire[i].sprite.setTextureRect(sf::IntRect(64 * ghSpriteFire[i].currentFrame, 0, 64, 64));
	}

	GHAnimatedSprite ghSpriteSpike[5];
	for (int i = 0; i < 5; i++)
	{
		ghSpriteSpike[i].sprite.setTexture(ref_spike1Texture);
		ghSpriteSpike[i].sprite.setPosition(256 + i * 64.0f, 512.0f);
		ghSpriteSpike[i].sprite.setTextureRect(sf::IntRect(64 * ghSpriteFire[i].currentFrame, 0, 64, 64));
	}



	GHAnimatedSprite ghSpriteGhost(ref_ghost1Texture);
	ghSpriteGhost.sprite.setPosition(200.0f, 400.0f);

	GHAnimatedSprite ghSpriteKey(ref_key1Texture);
	ghSpriteKey.sprite.setPosition(1700.0f, 1000.0f);



	bool haveTreasure[3];
	for (int i = 0; i < 3; i++)
	{
		haveTreasure[i] = false;
	}
	int treasureCount = 0;
	sf::Font font;
	if (!font.loadFromFile("pixel.ttf"))
	{
		return EXIT_FAILURE;
	}
	sf::Text treasureText;
	treasureText.setString("TREASURE:  " + toString(treasureCount));
	treasureText.setFont(font);
	treasureText.setCharacterSize(45);
	treasureText.setColor(sf::Color::Yellow);

	bool haveKey = false;
	int keyCount = 0;
	sf::Text keyText;
	keyText.setString("KEYS:  " + toString(keyCount));
	keyText.setFont(font);
	keyText.setCharacterSize(45);
	keyText.setColor(sf::Color::Yellow);

	bool moveRight = false;


	// clock variables for animated sprite frame rate
	sf::Clock clock1;
	sf::Time elapsed1;
	float timeSinceLastFrameAsFloat = 0.0f;
	float lastTimeAsFloat = 0.0f;

	// WELCOME PAGE
	sf::Texture welcomeScreen;
	if (welcomeScreen.loadFromFile("TitlePage.png"))
	{
		// error
	}
	sf::Sprite welcomePage;
	welcomePage.setTexture(welcomeScreen);
	welcomePage.setTextureRect(sf::IntRect(0, 0, 800, 600));

	/*
	// GAME OVER SCREEN
	sf::Texture gameOverT;
	if (welcomeScreen.loadFromFile("GameOver.png"))
	{
		// error
	}
	sf::Sprite gameOver;
	gameOver.setTexture(gameOverT);
	gameOver.setTextureRect(sf::IntRect(0, 0, 800, 600));
	*/

	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("Smb_under.ogg")) 
	{
		//return EXIT_FAILURE;
	}
	// Play the music
	music.play(); //TODO RE-ENABLE

	sf::Texture collectedKeyT;
	collectedKeyT.loadFromFile("SuccessKey.png");
	{
		//error
	}
	sf::Sprite collectedKey;
	collectedKey.setTexture(collectedKeyT);
	collectedKey.setTextureRect(sf::IntRect(0, 0, 64, 64));
	collectedKey.setPosition(0, 536);

	sf::Texture playerSpriteT;
	playerSpriteT.loadFromFile("PlayerSprite.png");
	{
		// error
	}
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerSpriteT);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	playerSprite.setPosition(64, 64);

	sf::Texture treasureSpriteT;
	treasureSpriteT.loadFromFile("TreasureSprite.png");
	{
		//error
	}
	sf::Sprite treasureSprite[3];
	for (int i = 0; i < 3; i++)
	{
		treasureSprite[i].setTexture(treasureSpriteT);
		treasureSprite[i].setTextureRect(sf::IntRect(0, 0, 64, 64));
		treasureSprite[0].setPosition(1408, 128);
		treasureSprite[1].setPosition(1408, 256);
		treasureSprite[2].setPosition(1152, 128);
	}
	//treasureSprite.setTexture(treasureSpriteT);
	//treasureSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	//treasureSprite.setPosition(1408, 128);

	
	// location vector of player
	sf::Vector2f playerWasAt;

	// WALLS
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
		wallBrick[i].setPosition(0, (i-12) * 64);
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
			//
			// Input game

		}
		//



		switch(newGame)
		{
		case Welcome:
			//cout << "start page";
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				newGame = Game;
			}

			window.clear();
			window.draw(welcomePage);
			window.display();
			break;

		case Game:

			Inputer(playerSprite, timeSinceLastFrameAsFloat);
			keyText.setString("KEYS:  " + toString(keyCount));
			treasureText.setString("TREASURE:  " + toString(treasureCount));

			//Beginning of the game state.
			//Collision check - WALLS
			keyText.setPosition(playerSprite.getPosition().x - 500, playerSprite.getPosition().y - 520);
			treasureText.setPosition(playerSprite.getPosition().x - 500, playerSprite.getPosition().y - 480);

			for (int i = 0; i < 130; i++) 
			{


				if ((abs((int)playerSprite.getPosition().x - (int)wallBrick[i].getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)wallBrick[i].getGlobalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)wallBrick[i].getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)wallBrick[i].getGlobalBounds().height)))) {

					cout << "WALL and Player collide\n";

					//If there was a collision, undo player movement;
					playerSprite.setPosition(playerWasAt.x, playerWasAt.y);

				}
			}

			//Collision check - FIRE
			for (int i = 0; i < 5; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteFire[i].sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteFire[i].sprite.getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)ghSpriteFire[i].sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteFire[i].sprite.getLocalBounds().height))))
				{

					cout << "FIRE and Player collide\n";

					//If there was a collision, kill player ;
					newGame = End;

				}
			}

			//Collision check - SPIKES
			for (int i = 0; i < 5; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteSpike[i].sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteSpike[i].sprite.getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)ghSpriteSpike[i].sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteSpike[i].sprite.getLocalBounds().height))))
				{

					cout << "SPIKES and Player collide\n";

					//If there was a collision, kill player ;
					newGame = End;
				}

			}


			//Collision check - GHOST
			if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteGhost.sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteGhost.sprite.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)ghSpriteGhost.sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteGhost.sprite.getLocalBounds().height))))
			{

				cout << "GHOST and Player collide\n";

				//If there was a collision, kill player ;
				newGame = End;
			}

			//Collision check - KEY
			if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteKey.sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteKey.sprite.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)ghSpriteKey.sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteKey.sprite.getLocalBounds().height))))
			{

				//cout << "KEY and Player collide\n";

				//If there was a collision, kill player ;
				
				haveKey = true;
				cout << "sprite key now true\n";
				keyCount = 1;
				
			}

			//Collision check - TREASURE
			for (int i = 0; i < 3; i++)
			{
				if ((abs((int)playerSprite.getPosition().x - (int)treasureSprite[i].getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)treasureSprite[i].getLocalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)treasureSprite[i].getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)treasureSprite[i].getLocalBounds().height))))
				{
					haveTreasure[i] = true;
					//cout << "KEY and Player collide\n";

					//If there was a collision, kill player ;

					//haveTreasure = true;
					cout << "treasure now true\n";
					treasureCount = 1;
				}
			}


			// ghost patrol
			if(moveRight) {

				ghSpriteGhost.sprite.move(64 * timeSinceLastFrameAsFloat, 0);
				

				if (ghSpriteGhost.sprite.getPosition().x > 320)
				{
					moveRight = false;
				}

			}
			
			if (!moveRight) {
				ghSpriteGhost.sprite.move(-64 * timeSinceLastFrameAsFloat, 0);

				if (ghSpriteGhost.sprite.getPosition().x < 64)
				{
					moveRight = true;
				}
			}

			

			//Change the camera according to the player position
			//view = window.getView();
			view.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);
			
			window.setView(view);

			//Timer here
			elapsed1 = clock1.getElapsedTime();
			timeSinceLastFrameAsFloat = elapsed1.asSeconds() - lastTimeAsFloat;
			lastTimeAsFloat = elapsed1.asSeconds();


			//Animated sprite updates (change frames)
			for (int i = 0; i < 5; i++)
			{
				ghSpriteFire[i].Update(timeSinceLastFrameAsFloat);
			}

			for (int i = 0; i < 5; i++)
			{
				ghSpriteSpike[i].Update(timeSinceLastFrameAsFloat);
			}

			ghSpriteGhost.Update(timeSinceLastFrameAsFloat);
			ghSpriteKey.Update(timeSinceLastFrameAsFloat);




			// Clear screen
			window.clear();

			// Draw sprites



			window.draw(ghSpriteGhost.sprite);

			if (haveKey == false)
			{
				window.draw(ghSpriteKey.sprite);
			}

			for (int i = 0; i < 3; i++)
			{
				if (haveTreasure[i] == false)
				{
					window.draw(treasureSprite[i]);
				}
			}




			for (int i = 0; i < 130; i++)
			{
				window.draw(wallBrick[i]);
			}

			for (int i = 0; i < 5; i++)
			{
				window.draw(ghSpriteFire[i].sprite);
			}

			for (int i = 0; i < 5; i++)
			{
				window.draw(ghSpriteSpike[i].sprite);
			}



			//window.draw(ghSpriteFire.sprite);


			// Draw the player (last so it's on top)
			window.draw(playerSprite);
			
			window.draw(keyText);
			window.draw(treasureText);

			// Update the window
			window.display();
			//End of the Game State

			myX++;
			break;

		case End:
			//cout << "endgame";
			playerSprite.setPosition(64, 64);
			//haveTreasure = false;
			haveKey = false;
			treasureCount = 0;
			keyCount = 0;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				newGame = Game;
			}
			window.clear();
			window.display();
			break;
		}


	}

	//return EXIT_SUCCESS;
	return 0;
}



void Inputer(sf::Sprite &playerSprite, float deltaTime) {

	// Check the boundry
	int boundry[4] = { 0,
		0,
		4000,
		4000 }; //TODO dynamically assign based on window size
	sf::Vector2f pos = playerSprite.getPosition();

	float velocity = 500.0f * deltaTime;
	//std::cout << deltaTime << std::endl;
	//cout << velocity << std::endl;

	// GH input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
	{
		cout << ("Left\n");
		if (pos.x > boundry[0]) playerSprite.move(-velocity, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cout << ("Right\n");
		if (pos.x < boundry[2]) playerSprite.move(velocity, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{
		cout << ("Up\n");
		if (pos.y > boundry[1]) playerSprite.move(0, -velocity);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{
		cout << ("Down\n");
		if (pos.y < boundry[3]) playerSprite.move(0, velocity);
	}
}



GHAnimatedSprite::GHAnimatedSprite(sf::Texture & myTexture) 
{ //no void for contstrctpr
	currentFrame = 0;
	timeSinceLastChange = 0.0f;

	sprite.setTexture(myTexture);
	sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));
}

GHAnimatedSprite::GHAnimatedSprite()
{ //no void for contstrctpr
	currentFrame = 0;
	timeSinceLastChange = 0.0f;

	//sprite.setTexture(myTexture);
	//sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));
}

void GHAnimatedSprite::Update(float timeSinceLastFrame) 
{
	timeSinceLastChange += timeSinceLastFrame;
	if (timeSinceLastChange >= 0.25f) {

		//cout << "timer hits 0.25 seconds\n";
		timeSinceLastChange = 0.0f; //reset the timer

									//increment the frame counter
		if (currentFrame >= 3) {
			currentFrame = 0;
		}
		else {
			currentFrame++;
		}

		//change the section of the texture
		sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));
	}
}