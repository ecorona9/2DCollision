#include "block.cpp"
#include "NumSlider.cpp"
#include "PrintableInfo.cpp"


using namespace std;
using namespace sf;

//window properties
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
//create player view
sf::View playerView;


//game objects
int keys[999] = { 0 };
Time timeSpeed(milliseconds(1000));
float x = 1000, y = 600, pw = 50,ph = 50, d = 50, speed = 0.199;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
sf::RectangleShape shape(Vector2f(pw, ph));
PrintableInfo<float> playerInfo;
float playerBounds[4] = { 0 };
float fallingSpeed = speed * 5, fallingVelocity = 0;

//text object
Text text;
Font font;

void loadObjectFiles();
void updateGame(Time&);
void renderObjects();

NumSlider xSlide(100, 1000, 6000);
Time elapsed;
float FPS = 0, iterationTime = 0, milliSeconds, microSeconds, Seconds, amountOfBlocks;

//background grid
sf::Texture gridTexture;
sf::Sprite grid;

//mouse info
float mouseX, mouseY, mouseRelativeX, mouseRelativeY, mouseBlockX, mouseBlockY;
sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

//grid/block cursor
sf::RectangleShape cursor(Vector2f(pw, ph));



int main()
{
	loadObjectFiles();

	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (event.type == Event::KeyPressed) keys[event.key.code] = true;
			if (event.type == Event::KeyReleased) keys[event.key.code] = false;
		}

		elapsed = clock.restart();

		updateGame(elapsed);

		renderObjects();
	}

	return EXIT_SUCCESS;
}


void loadObjectFiles()
{
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(100, 100);

	playerInfo.addInfo("x", x);
	playerInfo.addInfo("y", y);
	playerInfo.addInfo("speed", speed);
	playerInfo.addInfo("playerBounds[0]: ", playerBounds[0]);
	playerInfo.addInfo("playerBounds[1]: ", playerBounds[1]);
	playerInfo.addInfo("playerBounds[2]: ", playerBounds[2]);
	playerInfo.addInfo("playerBounds[3]: ", playerBounds[3]);
	playerInfo.addInfo("FPS: ", FPS);
	playerInfo.addInfo("iteration time: ", iterationTime);
	playerInfo.addInfo("seconds: ", Seconds);
	playerInfo.addInfo("milli seconds: ", milliSeconds);
	playerInfo.addInfo("micro seconds: ", microSeconds);
	playerInfo.addInfo("mouse x: ", mouseX);
	playerInfo.addInfo("mouse y: ", mouseY);
	playerInfo.addInfo("mouse relative x: ", mouseRelativeX);
	playerInfo.addInfo("mouse relative y: ", mouseRelativeY);
	playerInfo.addInfo("mouse Block x: ", mouseBlockX);
	playerInfo.addInfo("mouse Block y: ", mouseBlockY);
	playerInfo.addInfo("amount of blocks: ", amountOfBlocks);



	//load text font and settings
	if (!font.loadFromFile("Resources/arial.ttf"))
	{
		cerr << "font not loaded error" << endl;
	}
	text.setCharacterSize(15);
	text.setFillColor(Color::Yellow);
	text.setFont(font);
	text.setPosition(20, 20);


	worldBlocks.push_front(new Block(300, 300, 50, 50));
	worldBlocks.push_front(new Block(300, 400, 50, 50));
	worldBlocks.push_front(new Block(400, 300, 50, 50));
	worldBlocks.push_front(new Block(400, 400, 50, 50));
	worldBlocks.push_front(new Block(500, 500, 1000, 100));
	worldBlocks.push_front(new Block(500, 651, 100, 1000));
	worldBlocks.push_front(new Block(1000, 1000, 100, 1000));

	if (!gridTexture.loadFromFile("gridImage.png"))
		cerr << "grid image failed to load..." << endl;
	
	//grid loader
	grid.setTexture(gridTexture, true);

	//view loader
	playerView.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	playerView.setCenter(x + 25, y + 25);


	//set view
	window.setView(playerView);

	//cursor stuff
	cursor.setFillColor(sf::Color(104, 149, 21));

}
//800,1000,300
NumSlider rSlide(0, 255, 0, 2000);
NumSlider gSlide(81, 200, 0, 2000);
NumSlider bSlide(0, 255, 255, 2000);

bool jumping = false;
float jumpForce = speed * 10;
Clock jumpingClock;

void updateGame(Time& timeElapsed)
{
	
	//check for keyboard interactions first
	if (keys[Keyboard::W] && !playerBounds[1]) y -= speed;
	if (keys[Keyboard::A] && !playerBounds[0]) x -= speed;
	if (keys[Keyboard::D] && !playerBounds[2]) x += speed;
	if (keys[Keyboard::S] && !playerBounds[3]) y += speed;
	/*if (!playerBounds[3] && !jumping) y += jumpForce;*/
	/*if ((keys[Keyboard::W] || keys[Keyboard::Space]) && playerBounds[3])
	{
		if(!jumping) jumpingClock.restart();
		jumping = true;
		if (jumpingClock.getElapsedTime().asMicroseconds() < seconds(3).asMicroseconds())
		{
			y -= jumpForce;
		}
		else
		{
			jumping = false;
		}
		
	}*/
	

	if (keys[Keyboard::Equal]) speed += 0.001f;
	if (keys[Keyboard::Subtract]) if(speed > 0) speed -= 0.001f;

	if (keys[Keyboard::Insert])
	{
		cout << "There are currently " << worldBlocks.size() << "world blocks in the game." << endl;
		cout << "Requesting block creation, enter x y w h...\t";
		float x, y, w, h;
		cin >> x >> y >> w >> h;
		worldBlocks.push_front(new Block(x, y, w, h));
	}

	if (keys[Keyboard::Enter])
	{
		cout << "Set player x y...\t";
		float nx, ny;
		cin >> nx >> ny;
		x = nx;
		y = ny;
	}

	if (keys[Keyboard::Up])
		playerView.zoom(1.001f);

	if (keys[Keyboard::Down])
		playerView.zoom(0.999f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool blockAlreadyUsed = false;
		for (Block *aBlock : worldBlocks)
		{
			if(mouseBlockX >= aBlock->x && mouseBlockX < aBlock->x + 50)
				if(mouseBlockY >= aBlock->y && mouseBlockY < aBlock->y + 50)
					blockAlreadyUsed = true;
		}
		if (blockAlreadyUsed)
		{
			cout << "Block already USED %$%$%$%$%$" << endl;
		}
		else
		{
			amountOfBlocks = worldBlocks.size();
			cout << "There are currently " << amountOfBlocks << "world blocks in the game." << endl;
			cout << "Requesting block creation, enter x y w h...\t";
			worldBlocks.push_front(new Block(mouseBlockX, mouseBlockY, 50, 50));
		}
		
	}

	Uint8 r, g, b;
	r = (Uint8)rSlide.tick();
	g = (Uint8)gSlide.tick();
	b = (Uint8)bSlide.tick();

	//update position object parameters
	shape.setPosition(x, y);
	shape.setFillColor(Color(r, g, b));

	/*if (x >= WINDOW_WIDTH + 1) x = -50;
	if (x <= -51) x = WINDOW_WIDTH;
	if (y >= WINDOW_HEIGHT + 1) y = -50;
	if (y <= -51) y = WINDOW_HEIGHT;*/

	//handle block collision see "block.cpp"
	updateCollision(x, y, pw, ph);
	playerBounds[0] = canMoveLeft();
	playerBounds[1] = canMoveUp();
	playerBounds[2] = canMoveRight();
	playerBounds[3] = canMoveDown();

	//update view position
	playerView.setCenter(x + 25, y + 25);
	window.setView(playerView);

	//text position update
	text.setPosition(x - 605, y - 325);

	//mouse update
	mousePosition = sf::Mouse::getPosition(window);
	mouseX = mousePosition.x;
	mouseY = mousePosition.y;

	mouseRelativeX = x + mousePosition.x - 615;
	mouseRelativeY = y + mousePosition.y - 335;
	 
	mouseBlockX = (int)(mouseRelativeX / 50) * 50;
	mouseBlockY = (int)(mouseRelativeY / 50) * 50;

	//cursor update
	cursor.setPosition(mouseBlockX, mouseBlockY);
}



void renderObjects()
{
	//update how long this took in terms of FPS
	FPS = seconds(1).asMicroseconds() / (elapsed.asMicroseconds());
	iterationTime = elapsed.asMicroseconds();
	Seconds = elapsed.asSeconds();
	milliSeconds = elapsed.asMilliseconds();
	microSeconds = elapsed.asMicroseconds();
	text.setString(playerInfo.str());

	window.clear();
	
	window.draw(grid);

	window.draw(shape);
	for (Block* block : worldBlocks)
		window.draw(block->shape);

	window.draw(cursor);

	window.draw(text);

	window.display();
}