#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;
using namespace std;

static Color collisionColor(79, 198, 67);
static float PI = 3.14159265f;
class Block
{
public:
	float x, y, width, height;
	int blockBounds[4] = { 0 };
	RectangleShape shape;

	Block() : x(200), y(200), width(50), height(50), shape(Vector2f(10, 10))
	{
		cout << "block created at x:" << x << " y: " << y << endl;
	};
	Block(float nx, float ny, float w, float h) : x(nx), y(ny), width(w), height(h)
	{
		shape.setPosition(x, y);
		shape.setSize(Vector2f(w, h));
		Color blockColor(51, 122, 44);
		shape.setFillColor(blockColor);
		cout << "block created at x:" << x << " y: " << y << endl;


	};
	~Block() {};

};

static list<Block*> worldBlocks;


//provide player x, y, width and height
static void updateCollision(float& x, float& y, float& pw, float& ph)
{
	for (Block* block : worldBlocks)
	{
		if (x <= block->x + block->width && x + pw >= block->x &&
			y <= block->y + block->height && y + ph >= block->y)
		{

			float dx = (block->x + block->width / 2) - (x + pw / 2);
			float dy = (block->y + block->height / 2) - (y + ph / 2);
			float angle = atan2(dy, dx) * 180 / PI;

			float upperLeft  = atan2((block->y + block->height / 2) - (block->y), (block->x + block->width / 2) - (block->x)) * 180 / PI;
			float upperRight = atan2((block->y + block->height / 2) - (block->y), (block->x + block->width / 2) - (block->x + block->width)) * 180 / PI;
			float lowerLeft  = atan2((block->y + block->height / 2) - (block->y + block->height), (block->x + block->width / 2) - (block->x)) * 180 / PI;
			float lowerRight = atan2((block->y + block->height / 2) - (block->y + block->height), (block->x + block->width / 2) - (block->x + block->width)) * 180 / PI;

			cout << "angle deteced " << angle << endl;

			/*if (abs(angle) < 45)
				block->blockBounds[2] = true;

			if (angle > -135 && angle < -45)
				block->blockBounds[1] = true;

			if (abs(angle) > 135 && abs(angle) < 180)
				block->blockBounds[0] = true;

			if (angle > 45 && angle < 135)
				block->blockBounds[3] = true;*/

			if (angle < upperLeft && angle > lowerLeft)
				block->blockBounds[2] = true;

			if (angle > lowerRight && angle < lowerLeft)
				block->blockBounds[1] = true;

			if (abs(angle) > upperRight && abs(angle) < 180)
				block->blockBounds[0] = true;

			if (angle > upperLeft && angle < upperRight)
				block->blockBounds[3] = true;



		}
		else
		{
			block->blockBounds[0] = false;
			block->blockBounds[1] = false;
			block->blockBounds[2] = false;
			block->blockBounds[3] = false;
		}
	}
}

static bool canMoveRight()
{
	for (Block* block : worldBlocks)
		if (block->blockBounds[2])
			return true;
	return false;
}
static bool canMoveLeft()
{
	for (Block* block : worldBlocks)
		if (block->blockBounds[0])
			return true;
	return false;
}
static bool canMoveUp()
{
	for (Block* block : worldBlocks)
		if (block->blockBounds[1])
			return true;
	return false;
}
static bool canMoveDown()
{
	for (Block* block : worldBlocks)
		if (block->blockBounds[3])
			return true;
	return false;
}