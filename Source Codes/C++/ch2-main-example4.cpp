// g++ main.cpp -o result -lsfml-graphics -lsfml-window -lsfml-system

#include "SFML/Graphics.hpp"

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Hello SFML Game !!!", sf::Style::Default);

sf::Vector2f playerPosition;
bool playerMovingRight = false;
bool playerMovingLeft = false;

sf::Texture skyTexture;
sf::Sprite skySprite;

sf::Texture bgTexture;
sf::Sprite bgSprite;

sf::Texture heroTexture;
sf::Sprite heroSprite;

void init() {

	skyTexture.loadFromFile("/root/SourceCodes/CPP/Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("/root/SourceCodes/CPP/Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	heroTexture.loadFromFile("/root/SourceCodes/CPP/Assets/graphics/Freya.png");
	heroSprite.setTexture(heroTexture);
	heroSprite.setPosition(sf::Vector2f(viewSize.x / 600, viewSize.y / 600));
	heroSprite.setOrigin(heroTexture.getSize().x / 600, heroTexture.getSize().y / 600);

}

void updateInput() {

	sf::Event event;

	// while there are pending events...
	while (window.pollEvent(event)) {

		//printf(" polling events \n");

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Right) {
				playerMovingRight= true;
			}
			if (event.key.code == sf::Keyboard::Left) {
				playerMovingLeft= true;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Right) {
				playerMovingRight = false;
			}
			if (event.key.code == sf::Keyboard::Left) {
				playerMovingLeft = false;
			}
		}
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			window.close();
	}
}


void update(float dt) {
	if (playerMovingLeft) {
		heroSprite.move(-150.0f * dt, 0);
	}
	if (playerMovingRight) {
		heroSprite.move(150.0f * dt, 0);
	}
}

void draw() {
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(heroSprite);
}

int main() {
	sf::Clock clock;
	init();

	while (window.isOpen()) {
		updateInput();

		sf::Time dt = clock.restart();
		update(dt.asSeconds());

		window.clear(sf::Color::Red);
		draw();
		window.display();
	}
	return 0;
}