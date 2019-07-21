#include <iostream>
#include <chrono>
#include "Console.h"
#include "Map.h"
#include "Vec.h"
#include "Snake.h"
#include "Fruit.h"
#include "Systems.h"

int main()
{
	const unsigned int width = 30;
	const unsigned int height = 16;
	const unsigned int scoreSpan = 1;
	Console console(width, height+scoreSpan);
	snake_t snake;
	fruit_t fruit;
	
	Map map{width, height};
	for (unsigned int row = 0; row < height; row++) {
		for (unsigned int col = 0; col < width; col++) {
			int value;
			if (row == 0 || row == height - 1) value = 1;
			else if (col == 0 || col == width - 1) value = 1;
			else value = 0;
			map.set(col, row, value);			
		}
	}

	auto prevTime = std::chrono::system_clock::now();
	float elapsedTime = 0.f;
	while (true) {
		auto currTime = std::chrono::system_clock::now();
		std::chrono::duration<float> duration = currTime - prevTime;
		float deltaTime = duration.count();
		if (deltaTime < 0.016) continue;
		prevTime = currTime;
		elapsedTime += deltaTime;
		
		console.setTile(L"Snake++ [FPS: %.2f, ETA: %.2f]", 1.f / deltaTime, elapsedTime);

		handleRestart(fruit, snake);
		handleSnakeMoves(snake, deltaTime);
		handleCollision(fruit, snake, map);
		handleFruitSpawn(fruit, snake, map, 5, deltaTime);
		handleFruitTaken(fruit, snake);
		handleConsoleDraw(fruit, snake, console, map);
	}
}