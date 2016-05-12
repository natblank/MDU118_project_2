
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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


};

enum Gamestate {Welcome, Game, End};


int main(int, char const**)
{
	Gamestate newGame = Welcome;

	//VIEW STUFF
	sf::View view;
	int myX = 0;

	//void Inputer(sf::RectangleShape &player);
	void Inputer(sf::Sprite &playerSprite);




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

	//
	//GH Animated Sprite
	GHAnimatedSprite ghSpriteFire(ref_fire1Texture);
	ghSpriteFire.sprite.setPosition(200.0f, 200.0f);

	GHAnimatedSprite ghSpriteSpike(ref_spike1Texture);
	ghSpriteSpike.sprite.setPosition(200.0f, 300.0f);

	GHAnimatedSprite ghSpriteGhost(ref_ghost1Texture);
	ghSpriteGhost.sprite.setPosition(200.0f, 400.0f);

	sf::Clock clock1;
	sf::Time elapsed1;
	float timeSinceLastFrameAsFloat = 0.0f;
	float lastTimeAsFloat = 0.0f;


	sf::Texture welcomeScreen;
	if (welcomeScreen.loadFromFile("TitlePage.png"))
	{
		// error
	}
	sf::Sprite welcomePage;
	welcomePage.setTexture(welcomeScreen);
	welcomePage.setTextureRect(sf::IntRect(0, 0, 800, 600));

	//
	// Load a sprite to display
	sf::Texture texture;
	if (!texture.loadFromFile("cute_image.png")) {
		//return EXIT_FAILURE;
		//error
	}
	sf::Sprite sprite(texture);
	sprite.setScale(0.5f, 0.5f);


	//
	// Create a graphical text to display
	sf::Font font;
	if (!font.loadFromFile("sansation.png")) 
	{
		//return EXIT_FAILURE;
	}
	sf::Text text("Hello SFML", font, 50);
	text.setColor(sf::Color::Black);


	//
	// Load a music to play
	sf::Music music;
	if (!music.openFromFile("TakeFive.mp3")) 
	{
		//return EXIT_FAILURE;
	}
	// Play the music
	//music.play(); //TODO RE-ENABLE

	sf::Texture playerSpriteT;
	playerSpriteT.loadFromFile("PlayerSprite.png");
	{
		// error
	}
	sf::Sprite playerSprite;
	playerSprite.setTexture(playerSpriteT);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	playerSprite.setPosition(64, 64);

	sf::CircleShape circlePlayer(50);
	circlePlayer.setFillColor(sf::Color(100,50,50));

	//sf::RectangleShape player(sf::Vector2f(100, 100));
	//player.setPosition(300, 300);
	//player.setFillColor(sf::Color::Blue);
	
	// location vector of player
	sf::Vector2f playerWasAt;

	//
	// Wall test
	sf::Texture wallBrickT;
	wallBrickT.loadFromFile("WallBrick.png");
	sf::Sprite wallBrick[102];

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
	for (int i = 49; i < 57; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(704 + (i - 48) * 64, 448);
	}
	for (int i = 58; i < 66; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1088, 576 + (i - 57) * 64);
	}
	for (int i = 67; i < 79; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1024 + (i - 66) * 64, 1152);
	}
	for (int i = 80; i < 92; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1856, 384 + (i - 79) * 64);
	}
	for (int i = 93; i < 102; i++)
	{
		wallBrick[i].setTexture(wallBrickT);
		wallBrick[i].setPosition(1216 + (i - 92) * 64, 448);
	}


	// Start the game loop
	while (window.isOpen())
	{

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Escape pressed: exit
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			
			// store the player's current position for collision check
			playerWasAt.x = playerSprite.getPosition().x;
			playerWasAt.y = playerSprite.getPosition().y;
			//
			// Input game
			Inputer(playerSprite);

		}
		//

		switch(newGame)
		{
		case Welcome:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				newGame = Game;
			}
			window.clear();
			window.draw(welcomePage);
			window.display();
			break;

		case Game:

			//Beginning of the game state.
			//Collision check
			//WALLS
			for (int i = 0; i < 102; i++) 
			{


				if ((abs((int)playerSprite.getPosition().x - (int)wallBrick[i].getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)wallBrick[i].getGlobalBounds().width) &&
					(abs((int)playerSprite.getPosition().y - (int)wallBrick[i].getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)wallBrick[i].getGlobalBounds().height)))) {

					std::cout << "Wall1 i and Player collide\n";

					//If there was a collision, undo player movement;
					playerSprite.setPosition(playerWasAt.x, playerWasAt.y);

				}
			}



			//Collision check
			//Fire
			if ((abs((int)playerSprite.getPosition().x - (int)ghSpriteFire.sprite.getPosition().x) * 2 < ((int)playerSprite.getGlobalBounds().width + (int)ghSpriteFire.sprite.getLocalBounds().width) &&
				(abs((int)playerSprite.getPosition().y - (int)ghSpriteFire.sprite.getPosition().y) * 2 < ((int)playerSprite.getGlobalBounds().height + (int)ghSpriteFire.sprite.getLocalBounds().height)))) {

				std::cout << "FIRE and Player collide\n";

				//If there was a collision, kill player ;

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
			ghSpriteFire.Update(timeSinceLastFrameAsFloat);
			ghSpriteSpike.Update(timeSinceLastFrameAsFloat);
			ghSpriteGhost.Update(timeSinceLastFrameAsFloat);



			// Clear screen
			window.clear();




			window.draw(ghSpriteFire.sprite);
			window.draw(ghSpriteSpike.sprite);
			window.draw(ghSpriteGhost.sprite);



			for (int i = 0; i < 102; i++)
			{
				window.draw(wallBrick[i]);
			}


			//window.draw(ghSpriteFire.sprite);


			// Draw the player circle (last so it's on top)
			window.draw(playerSprite);



			// Update the window
			window.display();
			//End of the Game State

			myX++;
			break;

		case End:
			break;
		}
		//state machine here
		//menu
		//game
		//end

	}

	//return EXIT_SUCCESS;
	return 0;
}



void Inputer(sf::Sprite &playerSprite) {

	// Check the boundry
	int boundry[4] = { 0,
		0,
		4000,
		4000 }; //TODO dynamically assign based on window size
	sf::Vector2f pos = playerSprite.getPosition();

	int velocity = 20;
	// GH input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		std::cout << ("Left\n");
		if (pos.x > boundry[0]) playerSprite.move(-velocity, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		std::cout << ("Right\n");
		if (pos.x < boundry[2]) playerSprite.move(velocity, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		std::cout << ("Up\n");
		if (pos.y > boundry[1]) playerSprite.move(0, -velocity);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		std::cout << ("Down\n");
		if (pos.y < boundry[3]) playerSprite.move(0, velocity);

	}

}

GHAnimatedSprite::GHAnimatedSprite(sf::Texture & myTexture) { //no void for contstrctpr
	currentFrame = 0;
	timeSinceLastChange = 0.0f;

	sprite.setTexture(myTexture);
	sprite.setTextureRect(sf::IntRect(64 * currentFrame, 0, 64, 64));


}

void GHAnimatedSprite::Update(float timeSinceLastFrame) {

	timeSinceLastChange += timeSinceLastFrame;
	if (timeSinceLastChange >= 0.25f) {

		std::cout << "timer hits 0.25 seconds\n";
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