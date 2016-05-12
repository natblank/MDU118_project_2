
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



int main(int, char const**)
{
	//VIEW STUFF
	sf::View view;
	int myX = 0;

	void Inputer(sf::RectangleShape &player);

	//Store the window information
	//c_Window myWindow(800, 600);

	//std::cout << "\nScreen size thingy is :: " << myWindow.widthOfScreenMinusObjectsSize(100) << "\n";

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

	sf::Texture fire1Texture;
	if (!fire1Texture.loadFromFile("FireSprite.png")) {
		//return EXIT_FAILURE;
		//error
	}
	//reference pointer to the texture
	sf::Texture &ref_fire1Texture = fire1Texture;

	//sf::Sprite fireTest(fire1Texture);



	//
	//GH Animated Sprite
	GHAnimatedSprite ghSpriteFire(ref_fire1Texture);
	ghSpriteFire.sprite.setPosition(200.0f, 200.0f);

	sf::Clock clock1;
	sf::Time elapsed1;
	float timeSinceLastFrameAsFloat = 0.0f;
	float lastTimeAsFloat = 0.0f;



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

	sf::CircleShape circlePlayer(50);
	circlePlayer.setFillColor(sf::Color(100,50,50));

	sf::RectangleShape player(sf::Vector2f(100, 100));
	player.setPosition(300, 300);
	player.setFillColor(sf::Color::Blue);


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

	//wallBrick[2].setTexture(wallBrickT);
	//allBrick[2].setPosition(200, 400);



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
			
			sf::Vector2f playerWasAt;
			playerWasAt.x = player.getPosition().x;
			playerWasAt.y = player.getPosition().y;
			//
			// Input game
			Inputer(player);

		}
		//
		//Collision check
		//WALLS
		for (int i = 0; i < 3; i++) {
			//(wallBrick[i]);

			if ((abs((int)player.getPosition().x - (int)wallBrick[i].getPosition().x) * 2 < ((int)player.getSize().x + (int)wallBrick[i].getGlobalBounds().width) &&
				(abs((int)player.getPosition().y - (int)wallBrick[i].getPosition().y) * 2 < ((int)player.getSize().y + (int)wallBrick[i].getGlobalBounds().height)))) {

				std::cout << "Wall1 i and Player collide\n";

				//If there was a collision, undo player movement;

			}
		}



		//Collision check
		//Fire
		if ((abs((int)player.getPosition().x - (int)ghSpriteFire.sprite.getPosition().x) * 2 < ((int)player.getSize().x + (int)ghSpriteFire.sprite.getLocalBounds().width) &&
			(abs((int)player.getPosition().y - (int)ghSpriteFire.sprite.getPosition().y) * 2 < ((int)player.getSize().y + (int)ghSpriteFire.sprite.getLocalBounds().height)))) {

			std::cout << "FIRE and Player collide\n";

			//If there was a collision, kill player ;

		}



		//Change the camera according to the player position
		//view = window.getView();
		view.setCenter(player.getPosition().x, player.getPosition().y);
		window.setView(view);

		//Timer here
		elapsed1 = clock1.getElapsedTime();
		timeSinceLastFrameAsFloat = elapsed1.asSeconds() - lastTimeAsFloat;
		lastTimeAsFloat = elapsed1.asSeconds();


		//Animated sprite updates (change frames)
		ghSpriteFire.Update(timeSinceLastFrameAsFloat);



		// Clear screen
		window.clear();

		// Draw the background sprite
		//window.draw(sprite);

		// Draw the string
		//window.draw(text);



		window.draw(ghSpriteFire.sprite);


		for (int i = 0; i < 102; i++) 
		{
			window.draw(wallBrick[i]);
		}


		window.draw(ghSpriteFire.sprite);


		// Draw the player circle (last so it's on top)
		window.draw(player);



		// Update the window
		window.display();

		myX++;
	}

	//return EXIT_SUCCESS;
	return 0;
}



void Inputer(sf::RectangleShape &player) {

	// Check the boundry
	int boundry[4] = { 0,
		0,
		4000,
		4000 }; //TODO dynamically assign based on window size
	sf::Vector2f pos = player.getPosition();

	int velocity = 20;
	// GH input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		std::cout << ("Left\n");
		if (pos.x > boundry[0]) player.move(-velocity, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

		std::cout << ("Right\n");
		if (pos.x < boundry[2]) player.move(velocity, 0);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		std::cout << ("Up\n");
		if (pos.y > boundry[1]) player.move(0, -velocity);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		std::cout << ("Down\n");
		if (pos.y < boundry[3]) player.move(0, velocity);

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