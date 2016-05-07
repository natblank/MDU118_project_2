#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;


class Sprite
{
public:
	enum SpriteType
	{
		SPIKES, WALL, FIRE, DOOR, TREASURE, KEY, PLAYER
	};
private:
	sf::Sprite m_sprite;
	SpriteType m_type;
	sf::Texture m_texture;
	sf::IntRect m_rectangle;

public:
	Sprite(sf::Sprite sprite, SpriteType type, sf::Texture texture, sf::IntRect rectangle)
	{
		sf::Sprite m_sprite
	}
	void setTexture(sf::Texture texture); //bool resetRect = false
	void setRectangle(sf::IntRect rectangle);
	sf::Texture getTexture(SpriteType m_type);
	sf::IntRect getRectangle(SpriteType m_type);
	sf::Sprite generateSprite(SpriteType m_type);
};

: m_type(type), m_texture(texture), m_rectangle(rectangle)

sf::Sprite Sprite::generateSprite(SpriteType m_type)
{
	sf::Sprite mySprite;
	mySprite.setTexture();
	mySprite.setTextureRect(sf::IntRect());
}

class SpriteGenerator : public Sprite
{
	sf::Vector2f m_position;
public:
	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition();
};












sf::Texture Sprite::getTexture(SpriteType m_type)
{
	switch (m_type)
	{
	case SPIKES:
	{
		sf::Texture spike;
		spike.loadFromFile("SpikeSprite.png");
		return spike;
	}
	case FIRE:
	{
		sf::Texture fire;
		fire.loadFromFile("FireSprite.png");
		return fire;
	}
	case WALL:
	{
		sf::Texture wall;
		wall.loadFromFile("WallSprite.png");
		return wall;
	}
	case DOOR:
	{
		sf::Texture door;
		door.loadFromFile("DoorSprite.png");
		return door;
	}
	case TREASURE:
	{
		sf::Texture treasure;
		treasure.loadFromFile("TreasureSprite.png");
		return treasure;
	}
	case KEY:
	{
		sf::Texture key;
		key.loadFromFile("KeySprite.png");
		return key;
	}
	case PLAYER:
	{
		sf::Texture player;
		player.loadFromFile("PlayerSprite.png");
		return player;
	}
	}
}

sf::IntRect Sprite::getRectangle(SpriteType m_type)
{
	switch (m_type)
	{
	case SPIKES:
		return sf::IntRect(0, 0, 64, 64);
	case FIRE:
		return sf::IntRect(0, 0, 64, 64);
	case WALL:
		return sf::IntRect(0, 0, 64, 64);
	case DOOR:
		return sf::IntRect(0, 0, 64, 64);
	case TREASURE:
		return sf::IntRect(0, 0, 64, 64);
	case KEY:
		return sf::IntRect(0, 0, 64, 64);
	case PLAYER:
		return sf::IntRect(0, 0, 64, 64);
	}
}

sf::Vector2f Sprite::getPosition()
{
	m_position;
}

void Sprite::setTexture(sf::Texture texture) //bool resetRect = false
{
	m_texture = texture;
}

void Sprite::setRectangle(sf::IntRect rectangle)
{
	m_rectangle = rectangle;
}

void Sprite::setPosition(sf::Vector2f position)
{
	m_position = position;
}

void clock(int frameNo)
{

}
/*sf::Sprite Sprite::getSprite(SpriteType, sf::Texture m_texture) 
{
	//sf::Texture texture;
	switch (m_type)
	{
	case SPIKES: 
		if (!m_texture.loadFromFile("SpikeSprite.png"))
		{
			// error
		}
		return SpikeSprite.setTexture(m_texture);
	}
}

class SpriteTime
{
public:
	void FrameCounter(int frameNos);
};

class SpriteImages
{
public:
	sf::Texture myTexture;
	int myframeNo;
	void FireSprite(sf::Texture tex, sf::IntRect pix, int frameNo);
	void SpikeSprite(sf::Texture tex, sf::IntRect pix, int frameNo);
};

class SpriteDisplay
{
public:
	int vecAx, vecBy;
	//void SpriteTexture(sf::Texture texA, sf::Texture texB);
	void SpriteVectors(int vecX, int vecY);
	void SpriteImage(sf::Sprite si);
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	sf::Clock clock;
	float elapsedAsfloat = 0;

	int trapSpriteFrameCount = 0;

	sf::Texture spike;
	if (!spike.loadFromFile("SpikeSprite.png"))
	{
		// error
	}

	sf::Sprite spikeSprite;
	spikeSprite.setTexture(spike);
	spikeSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	spikeSprite.setPosition(sf::Vector2f(0, 115));

	sf::Texture fire;
	if (!fire.loadFromFile("FireSprite.png")) 
	{
		//error
	}

	sf::Sprite fireSprite;
	fireSprite.setTexture(fire);
	fireSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	fireSprite.setPosition(sf::Vector2f(0, 50));


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		 // time
		sf::Time elapsed1 = clock.getElapsedTime();
		//cout << elapsed1.asSeconds() << endl;
		elapsedAsfloat = elapsed1.asSeconds();

		if (elapsedAsfloat > 0.2f) 
		{

			//cout << "Time is now higher than 0.2";

			if (trapSpriteFrameCount < 3)
			{
				trapSpriteFrameCount++;
			}
			else
			{
				trapSpriteFrameCount = 0;
			}

			fireSprite.setTextureRect(sf::IntRect(64 * trapSpriteFrameCount, 0, 64, 64));
			spikeSprite.setTextureRect(sf::IntRect(64 * trapSpriteFrameCount, 0, 64, 64));

			clock.restart();
		}

		


		// black out the render window
		window.clear();
		// draw the shape
		window.draw(shape);
		window.draw(fireSprite);
		window.draw(spikeSprite);

		window.display();
	}

	return 0;
}

void SpriteTime::FrameCounter(int frameNos)
{
	sf::Clock clock;
	float elapsedAsfloat = 0;
	sf::Time elapsed1 = clock.getElapsedTime();
	elapsedAsfloat = elapsed1.asSeconds();
	int spriteFrameCount = 0;

	if (elapsedAsfloat > 0.2f)
	{
		if (spriteFrameCount < frameNos)
		{
			spriteFrameCount++;
		}
		else
		{
			spriteFrameCount = 0;
		}
		
		clock.restart();
	}
}

void SpriteImages::FireSprite(sf::Texture tex, sf::IntRect pix, int frameNo)
{
	if (!tex.loadFromFile("SpikeSprite.png"))
	{
		// error
	}
	pix = sf::IntRect(0, 0, 64, 64);
	frameNo = 3;
}

void SpriteImages::SpikeSprite(sf::Texture tex, sf::IntRect pix, int frameNo)
{
	if (!tex.loadFromFile("FireSprite.png"))
	{
		//error
	}
	pix = sf::IntRect(0, 0, 64, 64);
	frameNo = 1;
}

void SpriteDisplay::SpriteTexture(sf::Texture texA, sf::Texture texB)
{
	// sf::Texture texA;
	if (!texA.loadFromFile("SpikeSprite.png"))
	{
		// error
	}

	// sf::Texture texB;
	if (!texB.loadFromFile("FireSprite.png"))
	{
		//error
	}
} 

void SpriteDisplay::SpriteVectors(int vecX, int vecY)
{
	//vectors
}

void SpriteDisplay::SpriteImage(sf::Sprite si)
{
	// sf::Sprite si;
	si.setTexture(spike);
	si.setTextureRect(sf::IntRect(0, 0, 64, 64));
	si.setPosition(sf::Vector2f(0, 115));
}
